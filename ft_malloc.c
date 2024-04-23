/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:42:07 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/12 20:59:41 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_malloc.h"

/*
	GROSSE MODIF A FAIRE ICI:
	mon premier bloc n'est pas placé au bon endroit
	doit etre sur un modulo de 16
*/

void	*tiny_alloc(size_t size)
{
	t_page	*page;
	t_block	*block;

	page = find_page(TINY);
	if (!page)
		page = create_page(TINY);
	if (!page)
		return (NULL);
	block = page->blocks;
	if (!block)
	{
		block = (void *)page + sizeof(t_page);
		block->size = size;
		block->next = NULL;
		block->used = 1;
		page->blocks = block;
	}
	else
	{
		while (block->next)
		{	
			if (block->used == 0)
				break ;
			block = block->next;
		}
		if (!block->next)
		{
			block->next = (void*)block + sizeof(t_block) + TINY;
			printf("%p\n", block->next);
			block = block->next;
		}
		block->size = size;
		block->used = 1;
		block->next = NULL;
	}
	page->used++;
	return ((void*)block + sizeof(t_block));
}

void	*small_alloc(size_t size)
{
	t_page	*page;
	t_block	*block;

	page = find_page(SMALL);
	if (!page)
		page = create_page(SMALL);
	if (!page)
		return (NULL);
	block = page->blocks;
	if (!block)
	{
		block = (void *)page + sizeof(t_page);
		block->size = size;
		block->next = NULL;
		block->used = 1;
		page->blocks = block;
	}
	else
	{
		while (block->next)
		{
			if (block->used == 0)
				break ;
			block = block->next;
		}
		if (!block->next)
			block->next = (void*)block + sizeof(t_block) + SMALL;
		block = block->next;
		block->size = size;
		block->used = 1;
		block->next = NULL;
	}
	page->used++;
	return ((void*)block + sizeof(t_block));
}

void	*large_alloc(size_t size)
{
	t_page	*new;

	new = create_large_page(size);
	if (!new)
		return NULL;
	t_block	*block;
	block = new->blocks;
	block->size = size;
	block->used = 1;
	block->next = NULL;
	return ((void*)block);
}

void	*ft_malloc(size_t size)
{
	if (size <= TINY)
		return (tiny_alloc(size));
	else if (size <= SMALL)
		return (small_alloc(size));
	else
		return (large_alloc(size));
	return NULL;
}