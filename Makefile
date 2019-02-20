# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychufist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/19 16:49:26 by ychufist          #+#    #+#              #
#    Updated: 2018/11/19 16:52:17 by ychufist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIBFT = ./libft/libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRC = parse.c ft_adds.c ft_ants.c ft_is.c ft_list_room.c ft_ways.c

OUT = $(SRC:.c=.o)

HDR = lem_in.h

all: lib $(NAME)

lib:
	make -C ./libft

$(NAME): $(OUT) $(LIBFT)
	gcc -o $(NAME) $(OUT) $(LIBFT)

%.o: %.c $(HDR)
	gcc $(FLAGS) -o $@ -c $< -I ./libft

clean:
	make clean -C ./libft
	/bin/rm -f $(OUT)
	/bin/rm -f *~

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)

re: fclean all