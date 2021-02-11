/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-lorentz-andrea.romeo
** File description:
** calloc
*/

#include "my.h"

void *calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return (NULL);
    if (nmemb > (__SIZE_MAX__ / size))
        return (NULL);
    size_t total = nmemb * size;
    char *ptr = malloc(nmemb * size);
    if (ptr == NULL)
        return (NULL);
    for (size_t i = 0; i < total; i++)
        ptr[i] = '\0';
    return (ptr);
}