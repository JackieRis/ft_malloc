/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:38:50 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 03:55:36 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_malloc.h"

void	free(void *ptr)
{
	t_page	*curr;
	//t_page	*prev;
	t_page	*page = get_page();
	size_t	i = 0;

	curr = page;
	//prev = NULL;
	while (curr)
	{
		if (ptr >= curr->addr && ptr < curr->addr + curr->size)
		{
			i = 0;
			while (i < curr->used)
			{
				if (curr->addr + (i * curr->type) == ptr)
				{
					//si address trouvée mais block->used == 1 alors free page
					if (curr->used == 1)
					{
						free_page(curr->addr);
						return ;
					}
					//si address trouvée, déplacer les blocs suivants vers la gauche
					while (i < curr->used - 1)
					{
						curr->blocks[i] = curr->blocks[i + 1];
						i++;
					}
					curr->used--;
					return ;
				}
				i++;
			}
		}
		curr = curr->next;
	}
}