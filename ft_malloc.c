/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:59:16 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 16:12:58 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

//void *mmap(void *addr, size_t length, int prot, int flags,
//           int fd, off_t offset);

void	*ft_malloc(size_t size)
{
	void *addr = NULL;
	size_t sz;

	sz = sysconf(_SC_PAGESIZE);

	//tiny allocation
	if (size <= sz)
	{
		printf("tiny allocation\n");
		addr = mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		return (addr);
	}

	//small allocation
	if (size <= sz * 100)
	{
		printf("small allocation\n");
		addr = mmap(NULL, sz * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		return (addr);
	}

	//large allocation
	if (size <= sz * 1000)
	{
		printf("large allocation\n");
		addr = mmap(NULL, sz * 1000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		return (addr);
	}
	//addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	return (addr);
}