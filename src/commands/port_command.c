/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** port_command
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

void port_command(_server *s_struct, char *buffer, int i)
{
    (void)buffer;
    (void)i;
    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    return;
}
