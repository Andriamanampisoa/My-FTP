/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** path_errors
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

static bool path_exist(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
        return (EXIT_FAILURE);
    fclose(file);
    return (EXIT_SUCCESS);
}

// Check if the path is a directory
static bool is_dir(const char *path)
{
    struct stat path_info;

    stat(path, &path_info);
    if (S_ISDIR(path_info.st_mode))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

bool check_path_type(const char *path)
{
    if (path_exist(path) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (is_dir(path) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
