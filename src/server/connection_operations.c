/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** connectionOperations
*/

#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "server.h"
#include "user.h"
#include "myftp.h"

// Initialize the socket list for clients
bool initialize_client_socket(_server *s_struct)
{
    s_struct->client_socket = malloc(sizeof(int) * 11);
    if (s_struct->client_socket == NULL)
        return (EXIT_FAILURE);
    if (malloc_user_info(s_struct) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    for (int i = 0; i <= 10; i++) {
        s_struct->client_socket[i] = -1;
    }
    return (EXIT_SUCCESS);
}

// Add client
void add_client(_server *s_struct)
{
    s_struct->max_sd = s_struct->socketFd;
    for (int i = 0; i <= s_struct->max_clients; i++) {
        s_struct->sd = s_struct->client_socket[i];
        if (s_struct->sd > 0)
            FD_SET(s_struct->sd, &s_struct->readfds);
        if (s_struct->sd > s_struct->max_sd)
            s_struct->max_sd = s_struct->sd;
    }
}

static void do_new_connection_loop(_server *s_struct)
{
    for (int i = 0; i <= s_struct->max_clients; i++) {
        if (s_struct->client_socket[i] == -1) {
            s_struct->client_socket[i] = s_struct->new_socket;
            s_struct->user->ip[i] = inet_ntoa(s_struct->sockInfo.sin_addr);
            s_struct->user->port[i] = ntohs(s_struct->sockInfo.sin_port);
            printf("[SERVER] Adding to list of sockets as %d\n", i);
            break;
        }
    }
    return;
}

// New Connection => link the connection between users and server
bool setup_new_connection(_server *s_struct)
{
    if (FD_ISSET(s_struct->socketFd, &s_struct->readfds)) {
        s_struct->new_socket = accept(s_struct->socketFd,
            (struct sockaddr*) &s_struct->sockInfo, &s_struct->sockInfoSize);
        if (s_struct->new_socket < 0) {
                perror("accept");
                return (EXIT_FAILURE);
        }
        printf("[SERVER] New connection : socket fd is %d, ip is: %s, \
            port: %d \n", s_struct->new_socket,
            inet_ntoa(s_struct->sockInfo.sin_addr),
            ntohs(s_struct->sockInfo.sin_port));
        write(s_struct->new_socket, "220\n", 4);
        s_struct->clients_connected++;
        do_new_connection_loop(s_struct);
    }
    return (EXIT_SUCCESS);
}

static void do_other_operation_cond(_server *s_struct, char *buffer, int i)
{
    char str[INET_ADDRSTRLEN];

    s_struct->valRead = read(s_struct->sd, buffer, 1024);
    if (s_struct->valRead == 0) {
        getpeername(s_struct->sd, (struct sockaddr*)&s_struct->sockInfo,
            (socklen_t *)&s_struct->sockInfoSize);
        printf("[SERVER] Host disconnected : ip %s, port %d \n",
            inet_ntop(AF_INET, &s_struct->sockInfo.sin_addr, str,
            INET_ADDRSTRLEN), ntohs(s_struct->sockInfo.sin_port));
        s_struct->user->ip[i] = NULL;
        s_struct->user->port[i] = 0;
        s_struct->clients_connected--;
        close(s_struct->sd);
        s_struct->client_socket[i] = -1;
        s_struct->user->is_logged[i] = false;
        s_struct->user->user_pending[i] = false;
    } else {
        get_user_commands(s_struct, buffer, i);
    }
    return;
}

void do_other_operation(_server *s_struct)
{
    char *buffer = malloc(sizeof(char) * 1025);

    for (int i = 0; i <= s_struct->max_clients; i++) {
        s_struct->sd = s_struct->client_socket[i];
        if (FD_ISSET(s_struct->sd, &s_struct->readfds)) {
            do_other_operation_cond(s_struct, buffer, i);
        }
    }
    free(buffer);
    return;
}
