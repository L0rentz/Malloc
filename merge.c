/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-lorentz-andrea.romeo
** File description:
** merge
*/

#include "my.h"

block_t merge_prev(block_t to_merge)
{
    int check = 0;
    do {
        if ((char *)to_merge - to_merge->prev->size == to_merge->prev->adr
        && to_merge->prev->freed == 1) {
            to_merge->prev->size += to_merge->size + to_merge->offset
                + to_merge->prev->offset + sizeof(struct s_block);
            to_merge->prev->offset = align_mem(to_merge->prev->size)
                - to_merge->prev->size;
            to_merge->prev->size -= to_merge->prev->offset;
            to_merge->prev->next = to_merge->next;
            to_merge->prev->adr =
                (char *)to_merge->prev + sizeof(struct s_block)
                + to_merge->prev->offset;
            to_merge->next->prev = to_merge->prev;
            to_merge = to_merge->prev;
        } else check = 1;
    }
    while (check == 0);
    return (to_merge);
}

void merge_next(block_t to_merge, block_t *head)
{
    int check = 0;
    do {
        if (to_merge->adr + to_merge->size == to_merge->next
        && to_merge->next->freed == 1 && to_merge->next != *head) {
            to_merge->size += to_merge->next->size + to_merge->next->offset
                + sizeof(struct s_block) + to_merge->offset;
            to_merge->offset = (align_mem(to_merge->size) - to_merge->size);
            to_merge->size -= to_merge->offset;
            to_merge->next = to_merge->next->next;
            to_merge->adr = (char *)to_merge + sizeof(struct s_block)
                + to_merge->offset;
            to_merge->next->prev = to_merge;
        } else check = 1;
    }
    while (check == 0);
}