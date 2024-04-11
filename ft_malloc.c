/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:42:07 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 03:21:53 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_malloc.h"

void	*tiny_alloc(size_t size)
{
	t_page	*page;
	void	*addr;

	page = find_page(TINY);
	if (!page)
		page = create_page(TINY);
	if (!page)
		return (NULL);
	addr = page->addr + (page->used * TINY);
	page->blocks[page->used] = size;
	page->used++;
	return (addr);
}

void	*small_alloc(size_t size)
{
	t_page	*page;
	void	*addr;

	page = find_page(SMALL);
	if (!page)
		page = create_page(SMALL);
	if (!page)
		return (NULL);
	addr = page->addr + (page->used * SMALL);
	page->blocks[page->used] = size;
	page->used++;
	return (addr);
}

void	*ft_malloc(size_t size)
{
	t_page	*page;
	void	*addr;

	if (size <= TINY)
		return (tiny_alloc(size));
	else if (size <= SMALL)
		return (small_alloc(size));
	else
	{
		page = create_page(size);
		if (!page)
			return (NULL);
		addr = page->addr;
		page->used++;
		return (addr);
	}
	return NULL;
}