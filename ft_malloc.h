/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:09:34 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/10 02:37:08 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <sys/mman.h>

typedef struct	s_page
{
	struct s_page	*next;
	void		*addr;
	size_t		size;
	size_t		used;
}				t_page;

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	show_alloc_mem();

#endif