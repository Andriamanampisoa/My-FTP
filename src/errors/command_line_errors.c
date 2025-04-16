/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** commandLineError
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myftp.h"

// Check if the string contains only digits
static bool check_if_is_degit(const char *str)
{
    while (*str != '\0') {
        if (!isdigit(*str))
            return (EXIT_FAILURE);
        str++;
    }
    return (EXIT_SUCCESS);
}

// Check if the path contains some forbidden characters
// f = forbidden character
// p = path
// Return true if the path contains the forbidden character
// Return false otherwise
static bool check_path_cond(const char p)
{
    char *ban_char = ",?\0";

    for (int j = 0; ban_char[j] != '\0'; j++) {
        if (p == ban_char[j])
            return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}

static bool check_path(const char *path)
{
    for (int i = 0; path[i] != '\0'; i++) {
        if (check_path_cond(path[i]) == EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// Check the command line when user execute the myftp
bool check_user_command_line(int ac, char **av)
{
    if (ac != 3)
        return (EXIT_FAILURE);
    if (check_if_is_degit(av[1]) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (check_path_type(av[2]) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (check_path(av[2]) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
