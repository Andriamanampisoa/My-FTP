/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** list_command
*/

#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "myftp.h"

static void exelute_ls_loop(FILE *fp, int data_fd, _server *s_struct, int i)
{
    char buffer[1024];

    while (fgets(buffer, 1024, fp) != NULL) {
        if (write(data_fd, buffer, strlen(buffer) + 1) == -1) {
            write(s_struct->client_socket[i], "425\n", 4);
            return;
        }
    }
}

static void execute_ls(_server *s_struct, int i)
{
    FILE *fp;
    int data_fd = -1;
    socklen_t dataAddrSize;
    struct sockaddr_in dataAddr;

    data_fd = accept(s_struct->dataFd[i], (struct sockaddr *)&dataAddr,
        &dataAddrSize);
    fp = popen("ls -l", "r");
    if (fp == NULL) {
        write(s_struct->client_socket[i], "425\n", 4);
        return;
    }
    exelute_ls_loop(fp, data_fd, s_struct, i);
    pclose(fp);
    close(s_struct->dataFd[i]);
    write(s_struct->client_socket[i], "226\n", 4);
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
            return (EXIT_FAILURE);
        }
    } else {
        strcat(tmp, "/");
        strcat(tmp, s_struct->user->current_dir[i]);
        strcat(tmp, "/");
        strcat(tmp, buffer);
        if (chdir(tmp) == -1) {
            return (EXIT_FAILURE);
        }
    }
    change_dir_update(s_struct, buffer, i);
    return (EXIT_SUCCESS);
}

static bool change_dir(_server *s_struct, char *buffer, int i)
{
    char tmp[1024] = {0};

    strcpy(tmp, s_struct->initial_server_dir);
    if (change_dir_cond(s_struct, buffer, tmp, i) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

static void check_and_get_path(_server *s_struct, char *path, int i)
{
    char *tmp = NULL;

    tmp = malloc(sizeof(char) * (strlen(s_struct->user->current_dir[i]) + 1));
    strcpy(tmp, s_struct->user->current_dir[i]);
    if (path == NULL) {
        write(s_struct->client_socket[i], "150\n", 4);
        execute_ls(s_struct, i);
        return;
    }
    if (change_dir(s_struct, path, i) == EXIT_FAILURE) {
        write(s_struct->client_socket[i], "450\n", 4);
        return;
    }
    write(s_struct->client_socket[i], "150\n", 4);
    execute_ls(s_struct, i);
    change_dir(s_struct, tmp, i);
    free(tmp);
}

void list_command(_server *s_struct, char *buffer, int i)
{
    pid_t pid_fork;

    if (s_struct->user->is_logged[i] == false) {
        write(s_struct->client_socket[i], "530\n", 4);
        return;
    }
    if (s_struct->currentMod == Undefined) {
        write(s_struct->client_socket[i], "425\n", 4);
        return;
    }
    pid_fork = fork();
    if (pid_fork == 0) {
        if (s_struct->currentMod == Passive) {
            check_and_get_path(s_struct, buffer, i);
        }
        exit(0);
    }
    s_struct->currentMod = Undefined;
}
