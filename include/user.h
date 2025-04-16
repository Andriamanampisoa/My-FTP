/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** user
*/

#pragma once

#include <stdbool.h>

typedef struct user {
    char **current_dir;
    char *initial_dir;
    char **prev_dir;
    int *pid;
    char *account;
    char *password;
    char **ip;
    int *port;
    bool *is_logged;
    bool *user_pending;
} _user;
