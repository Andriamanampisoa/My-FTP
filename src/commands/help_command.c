/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** help_command
*/

#include <unistd.h>
#include "server.h"

void help_command(_server *s_struct, char *buffer, int i)
{
    (void)buffer;
    (void)i;
    write(s_struct->client_socket[i], "214\n", 4);
    return;
}
