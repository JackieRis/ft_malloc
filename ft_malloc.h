/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:09:34 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/05/01 18:11:42 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include "libft/libft.h"

#define TINY 128
#define SMALL 1024
#define	GET_MEM(size)mmap(NULL, size, PROT_READ| PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)

typedef struct	s_block
{
	struct s_block	*next;
	int			used;
	size_t		size;
}				t_block;

/*
	My allocation's page storage
	TYPE: type of the page, SMALL, TINY OR LARGE
	SIZE: only usefull for LARGE allocation, basically size allocated
	USED: number of blocks used in this page
	BLOCKS: block's list
*/
typedef struct	s_page
{
	struct s_page	*next;
	int			type;
	size_t		size;
	int			used;
	t_block		*blocks;
}				t_page;


void	move_mem(void** ref);
t_page	*create_page(int type);
t_page	*create_large_page(size_t size);
void	show_alloc_mem();
void	free_page(void *addr);
void	*find_page(int type);
void	*ft_malloc(size_t size);
void 	free(void *addr);
void	*get_page();

#endif