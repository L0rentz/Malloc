/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-lorentz-andrea.romeo
** File description:
** my
*/

#ifndef MY_H_
#define MY_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define align_mem(size) (((size) + (8 - 1)) &~ (8 - 1))
#define align_page(x, y) (((((x) - 1) / (y * 2)) * (y * 2)) + (y * 2))

typedef struct s_block {
    int freed;
    int offset;
    void *adr;
    size_t size;
    struct s_block *next;
    struct s_block *prev;
} *block_t;

block_t merge_prev(block_t to_merge);
void merge_next(block_t to_merge, block_t *head);
block_t push_block(size_t to_alloc, block_t *head);
block_t select_block(size_t size, block_t *head);
void split_block(size_t size, block_t bestfit, block_t *head);

#endif /* !MY_H_ */