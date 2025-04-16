/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** initServerStruct
*/

#include <stdbool.h>
#include <stdlib.h>
#include "server.h"
#include "myftp.h"

bool init_server_struct(_server *s_struct)
{
    s_struct->socketFd = 0;
    s_struct->dataFd = 0;
    s_struct->port = 0;
    s_struct->client_socket = 0;
    s_struct->opt = 1;
    s_struct->max_sd = 0;
    s_struct->sd = 0;
    s_struct->nextSocket = 0;
    s_struct->max_clients = 10;
    s_struct->new_socket = 0;
    s_struct->valRead = 0;
    s_struct->clients_connected = 0;
    s_struct->path = NULL;
    s_struct->currentMod = Undefined;
    s_struct->user = malloc(sizeof(_user));
    s_struct->initial_server_dir = NULL;
    init_user_struct(s_struct->user);
    return (EXIT_SUCCESS);
}
