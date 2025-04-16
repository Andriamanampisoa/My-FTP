/*
** EPITECH PROJECT, 2024
** B-NWP-400-NAN-4-1-myftp-toavina.andriamanampisoa
** File description:
** help
*/

#include <stdio.h>

// Displays the usage of the myftp
void display_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("       port is the port number on which the");
    printf(" server socket listens\n");
    printf("       path is the path to the home directory ");
    printf("for the Anonymous user\n");
    return;
}
