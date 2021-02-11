/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-lorentz-andrea.romeo
** File description:
** reallocarray
*/

#include "my.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return (NULL);
    if (nmemb > (__SIZE_MAX__ / size))
        return (NULL);
    return (realloc(ptr, nmemb * size));
}