/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:09:34 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 01:55:47 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include "libft/libft.h"

#define TINY 128
#define SMALL 1024
#define	GET_MEM(size)mmap(NULL, size, PROT_READ| PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)

typedef struct	s_page
{
	struct s_page	*next;
	void		*addr;
	int			type;
	size_t		size;
	size_t		used;
	//pointer to stock blocks_used_size
	size_t 		*blocks;
}				t_page;

void	move_mem(void** ref);
t_page	*create_page(int type);
void	show_mem();
void	free_page(void *addr);

#endif