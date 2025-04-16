/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** cdup_command
*/

#include <unistd.h>
#include <string.h>
#include "server.h"
#include "myftp.h"

static void cdup_previous_dir(_server *s_struct, char *buffer, int i)
{
    int size = strlen(s_struct->user->current_dir[i]);
    int end_back_s = count_slash(s_struct->user->current_dir[i]);

    if (end_back_s == 0) {
        write(s_struct->client_socket[i], "200\n", 4);
        return;
    }
    if (chdir(buffer) == -1) {
        write(s_struct->client_socket[i], "550\n", 4);
        return;
    }
    if (s_struct->user->current_dir[i][size - 1] == '/')
        s_struct->user->current_dir[i][size - 1] = '\0';
    for (int k = size - 1; k >= 0; k--) {
        if (s_struct->user->current_dir[i][k] == '/') {
            s_struct->user->current_dir[i][k] = '\0';
            break;
        }
    }
    write(s_struct->client_socket[i], "200\n", 4);
}

void cdup_command(_server *s_struct, char *buffer, int i)
{
    (void)buffer;
    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    cdup_previous_dir(s_struct, "..", i);
    return;
}
