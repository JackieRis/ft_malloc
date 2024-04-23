/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:39:13 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/12 21:00:07 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "ft_malloc.h"

static	t_page	*page;

void	*get_page()
{
	return (page);
}

t_page	*create_page(int type)
{
	t_page	*it;
	t_page	*new;
	size_t	alloc_size;
	size_t	sz;

	sz = getpagesize();
	alloc_size = 100 * type + sizeof(t_page) + 16 + (100 * sizeof(t_block));
	alloc_size = ((int)(alloc_size / sz) + 1) * sz;
	//printf("%lu\n", alloc_size);
	new = GET_MEM(alloc_size);
	if (new == MAP_FAILED)
		return NULL;
	new->next = NULL;
	new->size = alloc_size;
	new->type = type;
	new->used = 0;
	new->blocks = NULL;
	it = page;
	if (!it)
		page = new;
	else
	{
		while(it->next)
			it = it->next;
		it->next = new;
	}
	return (new);
}

t_page	*create_large_page(size_t size)
{
	t_page	*it;
	t_page	*new;
	size_t	sz;
	size_t	alloc_size;

	sz = getpagesize();
	alloc_size = size + sizeof(t_page) + 16 + sizeof(t_block);
	alloc_size = ((int)(alloc_size / sz) + 1) * sz;
	new = GET_MEM(alloc_size);
	if (new == MAP_FAILED)
		return NULL;
	new->next = NULL;
	new->size = alloc_size;
	new->type = 0;
	new->used = 0;
	new->blocks = (void*)new + sizeof(new);
	it = page;
	if (!it)
		page = new;
	else
	{
		while(it->next)
			it = it->next;
		it->next = new;
	}
	return (new);
}

void	*find_page(int type)
{
	t_page	*it;

	it = page;
	while(it)
	{
		if (it->type == type && it->used < 100)
			return (it);
		it = it->next;
	}
	return (NULL);
}

void	show_alloc_mem()
{
	t_page	*it;
	t_block	*blocks;

	if (page)
	{
		it = page;
		while(it)
		{
			if (it->type == TINY)
			{
				printf("TINY : %p\n", it);
				blocks = it->blocks;
				while (blocks)
				{
					if (blocks->used == 1)
						printf("%p - %p : %lu\n", blocks, blocks + blocks->size, blocks->size);
					blocks = blocks->next;
				}
			}
			else if (it->type == SMALL)
			{
				printf("SMALL : %p\n", it);
				blocks = it->blocks;
				while (blocks)
				{
					printf("%p - %p : %lu\n", blocks, blocks + blocks->size, blocks->size);
					blocks = blocks->next;
				}
			}
			else
				printf("LARGE : %p\n", it);
			it = it->next;
		}
	}
	else
		printf("No memory allocated\n");
}

void	free_page(void *addr)
{
	t_page	*curr;
	t_page	*prev;

	curr = page;
	prev = page;

	while(curr)
	{
		//printf("curr: %p\n", curr);
		if (addr >= (void*)curr && curr->next == NULL)
		{
			if (prev == curr)
				page = NULL;
			else
				prev->next = NULL;
			if (munmap(curr, curr->size) == 0)
				curr = NULL;
				
			break ;
		}
		else if (addr >= (void*)curr && addr < (void*)curr->next)
		{
			if (prev == curr)
				page = curr->next;
			else
				prev->next = curr->next;
			if (munmap(curr, curr->size) == 0)
				curr = NULL;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	
}

/*

getpagesize() = 16384
100 blocks
128o


int i = 1;
int j;
int sz = getpagesize();
int rest = 100;
total = 100 * TINY + sizeof(t_page) + 16 + (100 * sizeof(size_t))
taille mini à allouer pour une tiny

sz = getpagesize()
total / sz


if (sz / 128 >= rest)
	ok
else
{
	rest -= sz / 128
}

*/