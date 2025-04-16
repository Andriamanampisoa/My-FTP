/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** setUpServeur
*/

#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "user.h"
#include "server.h"
#include "myftp.h"

/*
static bool run_server_cond(_server *s_struct, int stats)
{
    FD_ZERO(&s_struct->readfds);
    FD_SET(s_struct->socketFd, &s_struct->readfds);
    add_client(s_struct);
    stats = select(s_struct->max_sd + 1, &s_struct->readfds, NULL,
        NULL, NULL);
    if ((stats < 0) && (errno != EINTR))
        printf("select error");
    if (setup_new_connection(s_struct) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    do_other_operation(s_struct);
    return (EXIT_SUCCESS);
}

static bool server_stop()
{
    char buffer[1024] = {0};
    ssize_t get_read = 0;

    get_read = read(STDIN_FILENO, buffer, sizeof(buffer));
    if (get_read == 0) {
        printf("[SERVER] Server closed.\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
*/

static bool run_server(_server *s_struct)
{
    int stats = 0;

    while (1) {
        FD_ZERO(&s_struct->readfds);
        FD_SET(s_struct->socketFd, &s_struct->readfds);
        add_client(s_struct);
        stats = select(s_struct->max_sd + 1, &s_struct->readfds, NULL,
            NULL, NULL);
        if ((stats < 0) && (errno != EINTR))
            printf("select error");
        if (setup_new_connection(s_struct) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        do_other_operation(s_struct);
    }
    return (EXIT_SUCCESS);
}

// Setup and run the server
// Return EXIT_FAILURE on failure
static bool setup_server(_server *s_struct)
{
    if (setsockopt(s_struct->socketFd, SOL_SOCKET, SO_REUSEADDR,
        &s_struct->opt, sizeof(s_struct->opt)) == -1) {
            perror("setsockopt");
            return (EXIT_FAILURE);
    }
    if (bind(s_struct->socketFd, (struct sockaddr *)&s_struct->sockInfo,
        sizeof(s_struct->sockInfo)) == -1) {
            perror("bind");
            return (EXIT_FAILURE);
    }
    if (listen(s_struct->socketFd, 3) < 0) {
        perror("listen");
        return (EXIT_FAILURE);
    }
    printf("[SERVER] Connection on %s %d\n",
        inet_ntoa(s_struct->sockInfo.sin_addr), s_struct->port);
    if (run_server(s_struct) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

// Create the server's base
// Return EXIT_FAILURE on failure
bool create_server(_server *s_struct, char **av)
{
    init_server_struct(s_struct);
    s_struct->port = atoi(av[1]);
    malloc_current_dir(s_struct);
    set_current_dir(s_struct, av[2]);
    if (initialize_client_socket(s_struct) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    s_struct->socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_struct->socketFd == -1) {
        perror("socket");
        return (EXIT_FAILURE);
    }
    s_struct->sockInfo.sin_family = AF_INET;
    s_struct->sockInfo.sin_port = htons(s_struct->port);
    s_struct->sockInfo.sin_addr.s_addr = INADDR_ANY;
    s_struct->sockInfoSize = sizeof(s_struct->sockInfo);
    if (setup_server(s_struct) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    close(s_struct->socketFd);
    free(s_struct->client_socket);
    return (EXIT_SUCCESS);
}
