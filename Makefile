# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 10:13:26 by wilson            #+#    #+#              #
#    Updated: 2023/11/18 14:22:08 by kallegre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

FLAG	=	-Wall -Werror -Wextra

LIBFT	=	libft/libft.a

SRC		=	main.c \
			parse.c \
			utils.c \
			parse_map.c \
			utils_parse.c \
			get_next_line.c \
			ray_casting.c \
			create_image.c \
			event.c \

OBJ		=	$(SRC:.c=.o)

all		:	$(NAME)

# $(NAME)	:	$(LIBFT) $(OBJ)
# 			clang $(FLAG) $(OBJ) -o $(NAME) $(LIBFT)

$(NAME)	:	$(LIBFT) $(OBJ)
			gcc $(FLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)

$(LIBFT):
			make -C libft

clean	:
			make clean -C libft
			rm -rf $(OBJ)

fclean	: 	clean
			rm -rf libft/libft.a
			rm -rf $(NAME)

re		:	fclean all