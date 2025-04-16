/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** pasv_command
*/

#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

void server_response(_server *s_struct, struct sockaddr_in *sockInfo, int i)
{
    char address[4];
    unsigned short port[2];

    if (listen(s_struct->dataFd[i], 1) < 0) {
        write(s_struct->client_socket[i], "425\n", 4);
        return;
    }
    sscanf(inet_ntoa(sockInfo->sin_addr), "%hhu.%hhu.%hhu.%hhu",
    &address[0], &address[1],
    &address[2], &address[3]);
    port[0] = ntohs(sockInfo->sin_port) / 256;
    port[1] = ntohs(sockInfo->sin_port) % 256;
    write(s_struct->client_socket[i], "227 ", 5);
    dprintf(s_struct->client_socket[i], "Entering Passive Mode "
    "(%hhu,%hhu,%hhu,%hhu,%hu,%hu)\r\n", address[0], address[1],
    address[2], address[3], port[0], port[1]);
    return;
}

static struct sockaddr_in set_the_sock_info(struct sockaddr_in *sockInfo)
{
    sockInfo->sin_family = AF_INET;
    sockInfo->sin_port = 0;
    sockInfo->sin_addr.s_addr = INADDR_ANY;
    return (*sockInfo);
}

void setup_pasv_command(_server *s_struct, int i)
{
    struct sockaddr_in sockInfo;
    socklen_t sockInfoSize = sizeof(sockInfo);

    s_struct->dataFd[i] = socket(AF_INET, SOCK_STREAM, 0);
    if (s_struct->socketFd == -1) {
        write(s_struct->client_socket[i], "425\n", 4);
        return;
    }
    memcpy(&sockInfo, &s_struct->sockInfo, sockInfoSize);
    sockInfo = set_the_sock_info(&sockInfo);
    sockInfoSize = sizeof(sockInfo);
    if (bind(s_struct->dataFd[i], (struct sockaddr *)&sockInfo,
        sizeof(sockInfo)) == -1) {
            write(s_struct->client_socket[i], "425\n", 4);
            return;
    }
    getsockname(s_struct->dataFd[i], (struct sockaddr *)&sockInfo,
        &sockInfoSize);
    server_response(s_struct, &sockInfo, i);
}

void pasv_command(_server *s_struct, char *buffer, int i)
{
    (void) buffer;
    s_struct->dataFd = malloc(sizeof(int) * s_struct->max_clients);
    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    setup_pasv_command(s_struct, i);
    s_struct->currentMod = Passive;
    return;
}
