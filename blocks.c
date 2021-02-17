/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-lorentz-andrea.romeo
** File description:
** blocks
*/

#include "my.h"

block_t push_block(size_t to_alloc, block_t *head)
{
    if ((*head) == NULL) {
        (*head) = sbrk(to_alloc);
        (*head)->freed = 1;
        (*head)->next = (*head), (*head)->prev = (*head);
        (*head)->size = to_alloc - sizeof(struct s_block);
        (*head)->adr = (char *)(*head) + sizeof(struct s_block);
        return ((*head));
    } else {
        block_t block = sbrk(to_alloc);
        block->freed = 1;
        block->next = (*head), block->prev = (*head)->prev;
        if ((*head)->next == (*head)) (*head)->next = block;
        else (*head)->prev->next = block;
        (*head)->prev = block;
        block->size = to_alloc - sizeof(struct s_block);
        block->adr = (char *)block + sizeof(struct s_block);
        block = merge_prev(block);
        return (block);
    }
}

block_t select_block(size_t size, block_t *head)
{
    block_t tmp = (*head), bestfit = NULL;
    size_t closest = __SIZE_MAX__;
    size_t to_find = size + sizeof(struct s_block);
    size_t to_alloc = align_page(size + sizeof(struct s_block), getpagesize());
    if (tmp != NULL) {
        do {
            if (tmp->size > to_find && tmp->size < closest
            && tmp->freed == 1) {
                closest = tmp->size;
                bestfit = tmp;
            }
            tmp = tmp->next;
        }
        while (tmp != (*head));
        if (bestfit == NULL) bestfit = push_block(to_alloc, head);
    }
    else tmp = push_block(to_alloc, head);
    if (bestfit == NULL) return (tmp);
    return (bestfit);
}

void split_block(size_t size, block_t bestfit)
{
    bestfit->freed = 0;
    if (bestfit->size == size) return;
    block_t split =
        (block_t)((char *)bestfit + sizeof(struct s_block) + size);
    split->freed = 1;
    split->next = bestfit->next;
    split->prev = bestfit;
    split->size = bestfit->size - sizeof(struct s_block) - size;
    split->adr = (char *)split + sizeof(struct s_block);
    bestfit->next = split;
    bestfit->size = size;
    split->next->prev = split;
    bestfit->adr = (char *)bestfit + sizeof(struct s_block);
}