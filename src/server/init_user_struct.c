/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** init_user_struct
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "server.h"
#include "user.h"

void set_current_dir(_server *s_struct, char *path)
{
    s_struct->user->initial_dir = malloc(sizeof(char) * (strlen(path) + 1));
    s_struct->initial_server_dir = malloc(sizeof(char) * 256);
    if (s_struct->user->initial_dir == NULL ||
        s_struct->initial_server_dir == NULL)
            exit(84);
    if (getcwd(s_struct->initial_server_dir, 256) == NULL)
        exit(84);
    for (int i = 0; i <= 10; i++) {
        strcpy(s_struct->user->current_dir[i], path);
    }
    if (chdir(path) == -1)
        exit(84);
    return;
}

static void malloc_prev_dir(_server *s_struct)
{
    s_struct->user->prev_dir = malloc(sizeof(char *) * 11);
    if (s_struct->user->prev_dir == NULL)
        exit(84);
    for (int i = 0; i <= 10; i++) {
        s_struct->user->prev_dir[i] = malloc(sizeof(char) * 256);
        if (s_struct->user->prev_dir[i] == NULL)
            exit(84);
    }
    return;
}

void malloc_current_dir(_server *s_struct)
{
    s_struct->user->current_dir = malloc(sizeof(char *) * 11);
    if (s_struct->user->current_dir == NULL)
        exit(84);
    for (int i = 0; i <= 10; i++) {
        s_struct->user->current_dir[i] = malloc(sizeof(char) * 256);
        if (s_struct->user->current_dir[i] == NULL)
            exit(84);
    }
    malloc_prev_dir(s_struct);
    return;
}

static void set_false(_server *s_struct)
{
    for (int i = 0; i <= 10; i++) {
        s_struct->user->is_logged[i] = false;
        s_struct->user->user_pending[i] = false;
    }
    return;
}

bool malloc_user_info(_server *s_struct)
{
    s_struct->user->ip = malloc(sizeof(char *) * 11);
    if (s_struct->user->ip == NULL)
        return (EXIT_FAILURE);
    for (int i = 0; i <= 10; i++) {
        s_struct->user->ip[i] = malloc(sizeof(char) * 16);
        if (s_struct->user->ip[i] == NULL)
            return (EXIT_FAILURE);
    }
    s_struct->user->port = malloc(sizeof(char) * 11);
    if (s_struct->user->port == NULL)
        return (EXIT_FAILURE);
    s_struct->user->is_logged = malloc(sizeof(bool) * 11);
    if (s_struct->user->is_logged == NULL)
        return (EXIT_FAILURE);
    s_struct->user->user_pending = malloc(sizeof(bool) * 11);
    if (s_struct->user->user_pending == NULL)
        return (EXIT_FAILURE);
    set_false(s_struct);
    return (EXIT_SUCCESS);
}

static bool malloc_user_pid(_user *user)
{
    user->pid = malloc(sizeof(int) * 11);
    if (user->pid == NULL)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

void init_user_struct(_user *user)
{
    user->account = "Anonymous";
    user->password = "";
    user->ip = NULL;
    user->port = NULL;
    user->is_logged = NULL;
    user->user_pending = NULL;
    user->current_dir = NULL;
    user->initial_dir = NULL;
    user->pid = NULL;
    user->pid = malloc(sizeof(int) * 11);
    for (int i = 0; i <= 10; i++)
        user->pid[i] = -2;
    if (malloc_user_pid(user) == EXIT_FAILURE)
        exit(84);
    return;
}
