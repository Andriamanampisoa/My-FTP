/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** stor_command
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "server.h"

// Check if the file descriptor is valid and close it
static bool receive_client_verif(ssize_t bytes_read, int fd)
{
    if (bytes_read == -1) {
        perror("Error reading from socket");
        close(fd);
        return (EXIT_FAILURE);
    }
    if (close(fd) == -1) {
        perror("Error closing file");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// Receive a file from the client
static bool receive_client_file(_server *s_struct, int fd, int i)
{
    char buffer[1024];
    ssize_t bytes_read = 0;
    ssize_t bytes_written = 0;
    socklen_t dataAddrSize;
    struct sockaddr_in dataAddr;
    int data_fd = -1;

    data_fd = accept(s_struct->dataFd[i], (struct sockaddr *)&dataAddr,
        &dataAddrSize);
    while ((bytes_read = read(data_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to file");
            close(fd);
            return (EXIT_FAILURE);
        }
    }
    if (receive_client_verif(bytes_read, fd) == EXIT_FAILURE)
        return (EXIT_FAILURE);
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

void stor_command(_server *s_struct, char *buffer, int i)
{
    (void)buffer;
    int fd = 0;
    if (pre_command_check(s_struct, i) == EXIT_FAILURE)
        return;
    fd = open(buffer, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        write(s_struct->client_socket[i], "450\n", 4);
        return;
    }
    write(s_struct->client_socket[i], "150\n", 4);
    if (receive_client_file(s_struct, fd, i) == EXIT_FAILURE)
        return;
    write(s_struct->client_socket[i], "226\n", 4);
    s_struct->currentMod = Undefined;
    return;
}
