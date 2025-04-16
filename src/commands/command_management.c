/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** command_management
*/

#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "server.h"
#include "myftp.h"

void (*commands_ptr[])(_server *s_struct, char *buffer, int i) = {
    &user_command,
    &pass_command,
    &cwd_command,
    &dele_command,
    &port_command,
    &retr_command,
    &stor_command,
    &list_command,
    &pwd_command,
    &noop_command,
    &pasv_command,
    &quit_command,
    &cdup_command,
    &help_command,
    NULL
};

int select_list_cmd(_server *s_struct, char *buffer, int i, int cmd_index)
{
    if (buffer != NULL)
        remove_r_and_n(buffer);
    commands_ptr[cmd_index](s_struct, buffer, i);
    return (0);
}

// Return -3 if the command's parameter is invalid
// Return EXIT_SUCCESS if the command's parameter is valid
// Return EXIT_FAILURE otherwise
static int check_command_second_cond(_server *s_struct, char *token,
    int b, int i)
{
    const char *commands_list2[] = {"PWD", "NOOP", "PASV", "QUIT", "CDUP",
        "HELP", NULL};
    const char *separator = " \t";
    char *tmp;

    if (strcmp(token, commands_list2[b]) == 0) {
        tmp = strtok(NULL, separator);
        if (tmp != NULL) {
            return (-3);
        } else {
            select_list_cmd(s_struct, token, i, (b + 8));
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_FAILURE);
}

// Check if the command is valid
// Return EXIT_SUCCESS if the command is valid
// Return EXIT_FAILURE otherwise
static bool check_command_second(_server *s_struct, char *token, int i)
{
    const char *commands_list2[] = {"PWD", "NOOP", "PASV", "QUIT", "CDUP",
        "HELP", NULL};
    int res = 0;

    for (int b = 0; commands_list2[b] != NULL; b++) {
        res = check_command_second_cond(s_struct, token, b, i);
        if (res == -3)
            return (EXIT_FAILURE);
        if (res == EXIT_SUCCESS)
            return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}

// Return -3 if the command's parameter is invalid
// Return EXIT_SUCCESS if the command's parameter is valid
// Return EXIT_FAILURE otherwise
static int check_command_first_cond(_server *s_struct, char *token,
    int a, int i)
{
    const char *commands_list1[] = {"USER", "PASS", "CWD", "DELE", "PORT",
        "RETR", "STOR", "LIST", NULL};
    const char *separator = " \t";
    char *tmp;
    char *tmp2;

    if (strcmp(token, commands_list1[a]) == 0) {
        tmp = strtok(NULL, separator);
        tmp2 = strtok(NULL, separator);
        if (tmp2 != NULL)
            return (EXIT_FAILURE);
        if (tmp == NULL && (strcmp(token, "PASS") != 0) &&
            (strcmp(token, "LIST") != 0)) {
                return (EXIT_FAILURE);
        } else {
            select_list_cmd(s_struct, tmp, i, a);
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_FAILURE);
}

// Check if the command is valid
// Return EXIT_SUCCESS if the command is valid
// Return EXIT_FAILURE otherwise
static bool check_command_first(_server *s_struct, char *buffer, int i)
{
    const char *commands_list1[] = {"USER", "PASS", "CWD", "DELE", "PORT",
        "RETR", "STOR", "LIST", NULL};
    const char *separator = " \t";
    char *token;

    token = strtok(buffer, separator);
    if (token == NULL)
        return (EXIT_FAILURE);
    remove_r_and_n(token);
    for (int a = 0; commands_list1[a] != NULL; a++) {
        if (check_command_first_cond(s_struct, token, a, i) == EXIT_SUCCESS)
            return (EXIT_SUCCESS);
    }
    if (check_command_second(s_struct, token, i) == EXIT_SUCCESS)
            return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

// Get user commands
// Return EXIT_SUCCESS if the command is valid
// Return EXIT_FAILURE otherwise
bool get_user_commands(_server *s_struct, char *buffer, int i)
{
    if (buffer == NULL)
        return (EXIT_FAILURE);
    if (check_command_first(s_struct, buffer, i) == EXIT_FAILURE) {
            write(s_struct->client_socket[i], "500\n", 4);
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

//bool get_user_commands(_server *s_struct, int i)
//{
//    printf("Client %d\n", i);
//    write(s_struct->client_socket[i], "Hello from server\n", 19);
//    return (EXIT_SUCCESS);
//}
