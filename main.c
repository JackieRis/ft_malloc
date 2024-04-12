/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:59:19 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/12 05:19:02 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_malloc.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	////int	length;
	////int *addr;

	////srand(2147483647);
	////if (argc != 2)
	////	return (1);
	////length = atoi(argv[1]);
	////addr = ft_malloc(length * sizeof(int));
	////if (addr == NULL)
	////	return 1;
	////for (int i = 0; i < length; i++)
	////	addr[i] = rand();
	////for (int i = 0; i < length; i++)
	////	printf("%d\n", addr[i]);
	////for (int i = 0; i < length; i++)
	////	ft_free(&addr[i]);
	////munmap(addr, length * sizeof(char));

	////size_t sz;
	////char *addr = "a";

	////sz = sysconf(_SC_PAGESIZE);
	////uintptr_t start = ((uintptr_t)addr & ~(sz -1));
	////uintptr_t end = start + 16383;
	////printf("%lx\n", start);
	////printf("end: %lx\n", end);
	////printf("%p\n", addr);

	///*///////////////////////////////////////////////*/

	//char	*addr = ft_malloc(50);
	//char	*addr2 = ft_malloc(42);
	//show_alloc_mem();
	//strcpy(addr, "Bonjour\n");
	//printf("%s", addr);
	//ft_free(addr);
	//ft_free(addr2);

	///*///////////////////////////////////////////////*/

	//t_page	*page = create_page(TINY);
	//t_page	*baguette = create_page(SMALL);
	//t_page	*poulet = create_page(SMALL);
	//show_mem();
	//free_page(page);
	//free_page(baguette);
	//free_page(poulet);

	///*///////////////////////////////////////////////*/

	char *addr = ft_malloc(50 * sizeof(char));

	printf("\n");
	show_alloc_mem();
	free(addr);
	//char *addr2 = ft_malloc(42 * sizeof(char));
	//int *addr3 = ft_malloc(100 * sizeof(int));
	//show_alloc_mem();
	//printf("\n");
	//free(addr2);
	//free(addr);
	//show_alloc_mem();
	//free(addr3);
	//show_alloc_mem();
	return 0;
}