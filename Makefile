# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 06:44:27 by tnguyen-          #+#    #+#              #
#    Updated: 2024/04/09 17:52:19 by tnguyen-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= malloc

SRCS	= main.c ft_malloc.c free.c

OBJ	= ${SRCS:.c=.o}

CC = gcc

FLAGS = -Wall -Werror -Wextra -pthread -fsanitize=address -fno-builtin -I.

all: ${NAME}

%.o:%.c ft_malloc.h
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:    ${OBJ}
	$(CC) ${FLAGS} $(OBJ) -o $(NAME)

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all