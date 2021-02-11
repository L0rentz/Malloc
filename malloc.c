/*
** EPITECH PROJECT, 2021
** bootstrap_malloc
** File description:
** utils
*/

#include "my.h"

static block_t head = NULL;

void *malloc(size_t size)
{
    if (size == 0)
        return (NULL);
    block_t bestfit = select_block(size, &head);
    split_block(size, bestfit, &head);
    return (bestfit->adr);
}

void free(void *adr)
{
    block_t tmp = head;
    int check = 0;
    if (adr != NULL && tmp != NULL) {
        do {
            if (tmp->adr == adr) {
                check = 1;
                break;
            }
            tmp = tmp->next;
        }
        while (tmp != head && check == 0);
        if (check == 0)
            fputs("free(): invalid pointer\n", stderr), abort();
        if (tmp->freed == 1)
            fputs("free(): double free detected\n", stderr), abort();
        tmp->freed = 1;
        tmp = merge_prev(tmp);
        merge_next(tmp, &head);
    }
}

void *realloc(void *ptr, size_t size)
{
    if (size == 0) {
        free(ptr);
        return (NULL);
    }
    if (ptr == NULL) return (malloc(size));
    block_t tmp = head;
    int check = 0;
    do {
        if (tmp->adr == ptr) {
                check = 1;
                break;
        } tmp = tmp->next;
    } while (tmp != head && check == 0);
    if (check == 0 || tmp->freed == 1) return (NULL);
    if (size == tmp->size) return (ptr);
    char *new_ptr = malloc(size);
    for (size_t i = 0; i < tmp->size && i < size; i++)
        new_ptr[i] = ((char *)tmp->adr)[i];
    free(tmp->adr);
    return (new_ptr);
}