/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** cwd_command
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "myftp.h"

static void previous_dir(_server *s_struct, char *buffer, int i)
{
    int size = strlen(s_struct->user->current_dir[i]);
    int end_back_s = count_slash(s_struct->user->current_dir[i]);

    if (end_back_s == 0) {
        write(s_struct->client_socket[i], "250\n", 4);
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
    write(s_struct->client_socket[i], "250\n", 4);
}

static void change_dir_update(_server *s_struct, char *buffer, int i)
{
    if (strcmp(s_struct->user->current_dir[i], "/") == 0) {
        s_struct->user->current_dir[i] = buffer;
    } else {
        if (check_end_slash(s_struct->user->current_dir[i]) == EXIT_SUCCESS)
            strcat(s_struct->user->current_dir[i], buffer);
        else {
            strcat(s_struct->user->current_dir[i], "/");
            strcat(s_struct->user->current_dir[i], buffer);
        }
    }
}

static bool change_dir_cond(_server *s_struct, char *buffer, char *tmp, int i)
{
    if (s_struct->user->current_dir[i][0] == '/' || buffer[0] == '/') {
        strcat(tmp, buffer);
        if (chdir(tmp) == -1) {
            write(s_struct->client_socket[i], "550\n", 4);
            return (EXIT_FAILURE);
        }
    } else {
        strcat(tmp, "/");
        strcat(tmp, s_struct->user->current_dir[i]);
        strcat(tmp, "/");
        strcat(tmp, buffer);
        if (chdir(tmp) == -1) {
            write(s_struct->client_socket[i], "550\n", 4);
            return (EXIT_FAILURE);
        }
    }
    change_dir_update(s_struct, buffer, i);
    return (EXIT_SUCCESS);
}

static void change_dir(_server *s_struct, char *buffer, int i)
{
    char tmp[1024] = {0};

    strcpy(tmp, s_struct->initial_server_dir);
    if (change_dir_cond(s_struct, buffer, tmp, i) == EXIT_FAILURE)
        return;
    write(s_struct->client_socket[i], "250\n", 4);
    return;
}

void cwd_command(_server *s_struct, char *buffer, int i)
{
    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    if (strcmp(buffer, "..") == 0) {
        previous_dir(s_struct, "..", i);
        return;
    }
    change_dir(s_struct, buffer, i);
    return;
}
