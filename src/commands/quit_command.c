/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** quit_command
*/

#include <unistd.h>
#include <stdio.h>
#include "server.h"
#include "myftp.h"
#include "user.h"

void quit_command(_server *s_struct, char *buffer, int i)
{
    (void)buffer;
    printf("[SERVER] Host disconnected : ip %s, port %d \n",
        s_struct->user->ip[i], s_struct->user->port[i]);
    s_struct->user->ip[i] = NULL;
    s_struct->user->port[i] = 0;
    s_struct->clients_connected--;
    close(s_struct->sd);
    s_struct->client_socket[i] = -1;
    s_struct->user->is_logged[i] = false;
    s_struct->user->user_pending[i] = false;
    return;
}
