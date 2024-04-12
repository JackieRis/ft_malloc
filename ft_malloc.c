/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:42:07 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/12 05:23:31 by tnguyen-         ###   ########.fr       */
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
		printf("block: %p\n", block);
		block->size = size;
		block->next = NULL;
		page->blocks = block;
	}
	else
	{
		while (block->next)
			block = block->next;
		block->next = block + sizeof(t_block);
		block = block->next;
		block->size = size;
		block->next = NULL;
	}
	page->used++;
	return ((void*)block);
}

void	*small_alloc(size_t size)
{
	(void)size;
	//t_page	*page;
	//void	*addr;

	//page = find_page(SMALL);
	//if (!page)
	//	page = create_page(SMALL);
	//if (!page)
	//	return (NULL);
	//addr = page->addr + (page->used * SMALL);
	//page->blocks[page->used] = size;
	//page->used++;
	//return (addr);
	return NULL;
}

void	*ft_malloc(size_t size)
{
	if (size <= TINY)
		return (tiny_alloc(size));
	else if (size <= SMALL)
		return (small_alloc(size));
	//else
	//{
	//	page = create_page(size);
	//	if (!page)
	//		return (NULL);
	//	addr = page->addr;
	//	page->used++;
	//	return (addr);
	//}
	return NULL;
}