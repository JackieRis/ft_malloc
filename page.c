/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:39:13 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 03:12:09 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "ft_malloc.h"

static	t_page	*page;

t_page	*create_page(int type)
{
	t_page	*it;
	t_page	*new;
	size_t	alloc_size;
	size_t	sz;

	sz = getpagesize();
	alloc_size = 100 * type + sizeof(t_page) + 16 + (100 * sizeof(size_t));
	alloc_size = ((int)(alloc_size / sz) + 1) * sz;
	//printf("%lu\n", alloc_size);
	new = GET_MEM(alloc_size);
	if (new == MAP_FAILED)
		return NULL;
	new->blocks = (void *)(new + sizeof(t_page));
	new->next = NULL;
	new->size = alloc_size;
	new->type = type;
	new->used = 0;
	new->addr = (void *)(new->blocks + (100 * sizeof(size_t)));
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

void	show_mem()
{
	t_page	*it;

	if (page)
	{
		it = page;
		while(it)
		{
			if (it->type == TINY)
				printf("TINY: %p\n", it);
			else if (it->type == SMALL)
				printf("SMALL: %p\n", it);
			else
				printf("LARGE: %p\n", it);
			it = it->next;
		}
	}
	else
		printf("Memory well free\n");
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