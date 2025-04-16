/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** pass_command
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

void pass_command(_server *s_struct, char *buffer, int i)
{
    if (s_struct->user->is_logged[i] == true &&
        s_struct->user->user_pending[i] == true) {
            write(s_struct->client_socket[i], "230\n", 4);
            return;
    }
    if (s_struct->user->user_pending[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    if (buffer == NULL) {
        s_struct->user->is_logged[i] = true;
        write(s_struct->client_socket[i], "230\n", 4);
        return;
    }
    if (strcmp(buffer, s_struct->user->password) != 0) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    s_struct->user->is_logged[i] = true;
    write(s_struct->client_socket[i], "230\n", 4);
}
