/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** user_command
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

void user_command(_server *s_struct, char *buffer, int i)
{
    if (s_struct->user->is_logged[i] == true &&
        s_struct->user->user_pending[i] == true) {
            write(s_struct->client_socket[i], "230\n", 4);
            return;
    }
    if (s_struct->user->is_logged[i] == false &&
        s_struct->user->user_pending[i] == true) {
            write(s_struct->client_socket[i], "331\n", 4);
            return;
    }
    if (strcmp(buffer, s_struct->user->account) != 0) {
        write(s_struct->client_socket[i], "331\n", 4);
        return;
    }
    s_struct->user->user_pending[i] = true;
    write(s_struct->client_socket[i], "331\n", 4);
    return;
}
