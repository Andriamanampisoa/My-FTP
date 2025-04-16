/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** server
*/

#pragma once

#include <stdbool.h>
#include <netinet/in.h>
#include <sys/select.h>
#include "user.h"


enum Mods {
    Active,
    Passive,
    Undefined
};

typedef struct server {
    struct sockaddr_in sockInfo;
    _user *user;
    socklen_t sockInfoSize;
    fd_set readfds;
    char *path;
    char *initial_server_dir;
    enum Mods currentMod;
    int *client_socket;
    int socketFd;
    int *dataFd;
    int port;
    int opt;
    int max_sd;
    int sd;
    int nextSocket;
    int max_clients;
    int new_socket;
    int valRead;
    int clients_connected;
} _server;
