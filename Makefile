# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 06:44:27 by tnguyen-          #+#    #+#              #
#    Updated: 2024/04/12 20:35:07 by tnguyen-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= malloc

SRCS	= main.c ft_malloc.c free.c page.c utils.c

LIBFT = libft/libft.a

OBJ	= ${SRCS:.c=.o}

CC = gcc

FLAGS = -Wall -Werror -Wextra -fno-builtin -fsanitize=address -I.

all: ${NAME}

${LIBFT}:
	make -C libft

%.o:%.c ft_malloc.h
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:    ${OBJ} ${LIBFT}
	$(CC) ${FLAGS} $(OBJ) ${LIBFT} -o $(NAME)

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all