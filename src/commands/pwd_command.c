/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** pwd_command
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "myftp.h"

static char *remove_end_slash(char *str)
{
    if (str[strlen(str) - 1] == '/')
        str[strlen(str) - 1] = '\0';
    return (str);
}

void pwd_command(_server *s_struct, char *buffer, int i)
{
    char *tmp = NULL;

    (void)buffer;
    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    tmp = malloc(sizeof(char) * strlen(s_struct->user->current_dir[i]) + 1);
    strcpy(tmp, s_struct->user->current_dir[i]);
    tmp = remove_end_slash(tmp);
    if (count_slash(tmp) == 0) {
        write(s_struct->client_socket[i], "257 ", 4);
        write(s_struct->client_socket[i], "/\n", 3);
        return;
    }
    write(s_struct->client_socket[i], "257 ", 4);
    write(s_struct->client_socket[i], "/", 2);
    write(s_struct->client_socket[i], tmp, strlen(tmp));
    write(s_struct->client_socket[i], "\n", 1);
    return;
}
