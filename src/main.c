/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** main
*/

#include <stdlib.h>
#include <string.h>
#include "myftp.h"

// Main of the prgram
int main(int ac, char **av)
{
    _server s_struct;

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
        return (0);
    }
    if (check_user_command_line(ac, av) == EXIT_FAILURE)
        return (84);
    if (create_server(&s_struct, av) == EXIT_FAILURE)
        return (84);
    return (0);
}
