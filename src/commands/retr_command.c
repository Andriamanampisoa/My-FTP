/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** retr_command
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

// Send file to client using data fd
static void send_file(_server *s_struct, FILE *file, int i)
{
    char buffer[1024];
    size_t bytes_read;
    int data_fd = -1;
    socklen_t dataAddrSize;
    struct sockaddr_in dataAddr;

    data_fd = accept(s_struct->dataFd[i], (struct sockaddr *)&dataAddr,
        &dataAddrSize);
    do {
        bytes_read = fread(buffer, 1, sizeof(buffer), file);
        write(data_fd, buffer, bytes_read);
    } while (bytes_read == 1024);
    close(s_struct->dataFd[i]);
    close(data_fd);
}

// Check if file exists
static bool check_the_path(_server *s_struct, FILE * file, int i)
{
    if (file == NULL) {
        write(s_struct->client_socket[i], "450\n", 4);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// Check if user is logged and if the current mode is defined
static bool pre_command_check(_server *s_struct, int i)
{
    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return (EXIT_FAILURE);
    }
    if (s_struct->currentMod == Undefined) {
        write(s_struct->client_socket[i], "425\n", 4);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// RETR command
void retr_command(_server *s_struct, char *buffer, int i)
{
    FILE *file;
    pid_t pid_fork;

    if (pre_command_check(s_struct, i) == EXIT_FAILURE)
        return;
    file = fopen(buffer, "r");
    if (check_the_path(s_struct, file, i) == EXIT_FAILURE)
        return;
    write(s_struct->client_socket[i], "150\n", 4);
    pid_fork = fork();
    if (pid_fork < 0)
        return;
    if (pid_fork == 0) {
        if (s_struct->currentMod == Passive) {
            send_file(s_struct, file, i);
            write(s_struct->client_socket[i], "226\n", 4);
        }
        exit(0);
    }
    s_struct->currentMod = Undefined;
}
