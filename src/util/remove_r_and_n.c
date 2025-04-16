/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** remove_r_and_n
*/

#include <stddef.h>

// Remove '\\r' and '\\n' from the buffer
void remove_r_and_n(char *buffer)
{
    if (buffer == NULL)
        return;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\r' || buffer[i] == '\n')
            buffer[i] = '\0';
    }
    return;
}
