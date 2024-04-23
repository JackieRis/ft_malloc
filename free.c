/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:38:50 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/12 20:39:45 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_malloc.h"

void	re_align_next_blocks(t_block *block)
{
	block->next = (void*)block + block->size;
	if (block->next->next != NULL)
		re_align_next_blocks(block->next);
}

void	free(void *ptr)
{
	(void)ptr;
	t_page	*curr;
	//t_page	*prev;
	t_page	*page = get_page();
	t_block	*blocks;

	curr = page;
	//prev = NULL;
	while (curr)
	{
		if (ptr >= (void*)curr && ptr < (void*)curr + curr->size)
		{
			t_block *prev;
			blocks = curr->blocks;
			if (curr->used <= 1)
			{
				free_page(curr);
				return ;
			}
			prev = NULL;
			while (blocks)
			{
				//si bloc trouvé
				if ((void *)blocks + sizeof(t_block) == ptr)
				{
					//supprimer le maillon de la chaine
					blocks->used = 0;
					blocks->size = 0;
					if (prev)
						prev->next = blocks->next;
					else
						blocks = blocks->next;
					if (blocks->next)
						re_align_next_blocks(blocks);
					curr->used--;
					return ;
				}
				prev = blocks;
				blocks = blocks->next;
			}
		}
		curr = curr->next;
	}
}