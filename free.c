/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:38:50 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 16:09:08 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/mman.h>

void	ft_free(void *ptr)
{
	size_t size;

	size = 0;
	while (((char *)ptr)[size])
		size++;
	munmap(ptr, size);
}