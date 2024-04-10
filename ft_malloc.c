/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:59:16 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/10 03:54:11 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "ft_malloc.h"

t_page	*page;

//void *mmap(void *addr, size_t length, int prot, int flags,
//           int fd, off_t offset);

void	init_list()
{
	page = mmap(NULL, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (page == MAP_FAILED)
	{
		printf("mmap failed\n");
		return ;
	}
	page->next = NULL;
	page->addr = NULL;
	page->used = 0;
	page->size = 0;
	page->blocks = NULL;
}

void	*tiny_alloc()
{
	t_page	*tmp;
	t_page	*new;
	size_t	sz;

	printf("tiny_alloc\n");
	sz = getpagesize();
	tmp = page;
	while (tmp->next)
		tmp = tmp->next;
	new = mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new == MAP_FAILED)
	{
		printf("mmap failed\n");
		return (NULL);
	}
	new->next = NULL;
	new->addr = new + sizeof(t_page);
	new->size = 128;
	new->used = 0;
	size_t num_blocks = getpagesize() / 128; // Nombre de blocs dans une page
    new->blocks = mmap(NULL, num_blocks * sizeof(size_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new->blocks == MAP_FAILED)
    {
        printf("mmap failed\n");
        return (NULL);
    }

    // Initialiser chaque élément de la liste de blocs à 0 (non utilisé)
    for (size_t i = 0; i < num_blocks; i++)
    {
        new->blocks[i] = 0;
    }
	tmp->next = new;
	return (new->addr);
}

void	*tiny_block(size_t size)
{
	t_page	*tmp;
	void	*ret;
	
	ret = NULL;
	tmp = page;
	while (tmp)
	{
		//find tiny page
		//here tmp->size should be 128 bytes (block size)
		if (tmp->size >= size && size < 128)
		{
			printf("found a tiny block\n");
			//assign to a free block
			ret = tmp->addr + (tmp->used * tmp->size);
			tmp->blocks[tmp->used] = size;
			tmp->used++;
			return (ret);
		}
		tmp = tmp->next;
	}
	if (!ret)
		ret = tiny_alloc();
	tmp = page;
	while (tmp->next)
		tmp = tmp->next;
	tmp->blocks[tmp->used] = size;
	tmp->used++;
	return (ret);
}

void	*ft_malloc(size_t size)
{
	if (!page)
		init_list();
	if (size <= 0)
		return (NULL);
	if (size <= 128)
		return (tiny_block(size));
	return (NULL);
}

void	show_alloc_mem()
{
	printf("\n");
	t_page	*tmp;

	tmp = page;
	while (tmp)
	{
		if (tmp->size == 128)
		{
			printf("TINY : %p\n", tmp->addr);
			for (size_t i = 0; i < tmp->used; i++)
			{
				printf("%p - %p : %lu bytes\n", tmp->addr + (i * tmp->size), tmp->addr + ((i + 1) * tmp->size), tmp->blocks[i]);
			}
		}
		
		tmp = tmp->next;
	}
}

void	ft_free(void *ptr)
{
	t_page	*tmp;

	tmp = page;
	while (tmp)
	{
		if (tmp->addr == ptr)
		{
			tmp->used--;
			return ;
		}
		tmp = tmp->next;
	}
}