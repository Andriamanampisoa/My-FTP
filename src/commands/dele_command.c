/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** dele_command
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

void dele_command(_server *s_struct, char *buffer, int i)
{
    int result = 0;

    (void)i;
    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    result = unlink(buffer);
    if (result != 0) {
        write(s_struct->client_socket[i], "550\n", 4);
    } else {
        write(s_struct->client_socket[i], "250\n", 4);
    }
    return;
}
