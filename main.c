/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:59:19 by tnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 16:08:59 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "ft_malloc.h"

int main(int argc, char **argv)
{
	int	length;
	int *addr;

	srand(2147483647);
	if (argc != 2)
		return (1);
	length = atoi(argv[1]);
	addr = ft_malloc(length * sizeof(int));
	if (addr == NULL)
		return 1;
	for (int i = 0; i < length; i++)
		addr[i] = rand();
	for (int i = 0; i < length; i++)
		printf("%d\n", addr[i]);
	for (int i = 0; i < length; i++)
		ft_free(&addr[i]);
	munmap(addr, length * sizeof(char));
	return 0;
}