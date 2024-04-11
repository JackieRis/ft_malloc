/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:39:13 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 02:13:00 by tnguyen-         ###   ########.fr       */
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
			printf("page: %p\n", it);
			printf("next: %p\n", it->next);
			printf("addr: %p\n", it->addr);
			printf("type: %d\n", it->type);
			printf("size: %zu\n", it->size);
			printf("used: %zu\n", it->used);
			printf("blocks: %p\n", it->blocks);
			it = it->next;
		}
	}
	else
		printf("Memory well free\n");
}

void	free_page(void *addr)
{
	t_page	*it;
	t_page	*tmp;

	it = page;
	tmp = page;

	while(it->next)
	{
		if (addr > it->addr && addr < it->next->addr)
		{
			printf("free\n");
			tmp->next = it->next;
			munmap(it, it->size);
			return ;
		}
		else 
			tmp = it;
		it = it->next;
	}
	printf("free\n");
	tmp->next = NULL;
	if (munmap(it, it->size) == 0)
	{	
		printf("Memory well free\n");
		page = NULL;
	}
	else
		printf("Error\n");
	
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