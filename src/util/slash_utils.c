/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** slash_utils
*/

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int count_slash(char *buffer)
{
    int count = 0;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '/')
            count++;
    }
    return (count);
}

bool check_end_slash(char *buffer)
{
    if (buffer[strlen(buffer) - 1] == '/')
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}
