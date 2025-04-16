/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** myftp
*/

#pragma once

#include "user.h"
#include "server.h"
#include <stdbool.h>

void display_help(void);
bool check_user_command_line(int ac, char **av);
bool init_server_struct(_server *s_struct);
bool create_server(_server *s_struct, char **av);
void add_client(_server *s_struct);
bool setup_new_connection(_server *s_struct);
void do_other_operation(_server *s_struct);
bool initialize_client_socket(_server *s_struct);
bool get_user_commands(_server *s_struct, char *buffer, int i);
void remove_r_and_n(char *buffer);
void quit_command(_server *s_struct, char *buffer, int i);
void user_command(_server *s_struct, char *buffer, int i);
void pass_command(_server *s_struct, char *buffer, int i);
void cwd_command(_server *s_struct, char *buffer, int i);
void dele_command(_server *s_struct, char *buffer, int i);
void port_command(_server *s_struct, char *buffer, int i);
void help_command(_server *s_struct, char *buffer, int i);
void retr_command(_server *s_struct, char *buffer, int i);
void stor_command(_server *s_struct, char *buffer, int i);
void list_command(_server *s_struct, char *buffer, int i);
void pwd_command(_server *s_struct, char *buffer, int i);
void noop_command(_server *s_struct, char *buffer, int i);
void pasv_command(_server *s_struct, char *buffer, int i);
void cdup_command(_server *s_struct, char *buffer, int i);
void init_user_struct(_user *user);
bool malloc_user_info(_server *s_struct);
void malloc_current_dir(_server *s_struct);
void set_current_dir(_server *s_struct, char *path);
bool check_path_type(const char *path);
int count_slash(char *buffer);
bool check_end_slash(char *buffer);
