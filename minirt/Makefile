# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 13:37:33 by ecamara           #+#    #+#              #
#    Updated: 2022/09/29 14:39:25 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

SRC =	src/optimization/potential_get_dis.c		\
		src/optimization/potential.c				\
		src/optimization/aux.c						\
		src/optimization/swap.c						\
		src/intersect/get_intersect_shapes.c	\
		src/intersect/intersect_launch.c		\
		src/intersect/intersect_sh.c			\
		src/intersect/intersect_shapes_aux.c	\
		src/intersect/intersect_shapes.c		\
		src/intersect/intersection.c			\
		src/intersect/launch_shadow.c			\
		src/input/check_shapes.c		\
		src/input/check_space.c			\
		src/input/check_values.c		\
		src/input/error.c				\
		src/input/get_input.c			\
		src/input/init_data.c			\
		src/input/read_file.c			\
		src/input/set_shapes.c			\
		src/input/set_space.c			\
		src/math/col_math.c			\
		src/math/couple_math1.c		\
		src/math/couple_math2.c		\
		src/math/couple_math3.c		\
		src/math/couple.c			\
		src/math/math.c				\
		src/math/matrix_math.c		\
		src/math/matrix_set.c		\
		src/math/uv.c		\
		src/render/color.c		\
		src/render/lighting.c	\
		src/render/rebound.c	\
		src/render/render.c		\
		src/render/shoot.c		\
		src/render/temp.c		\
		src/skybox/skybox.c		\
		src/skybox/skybox_aux.c		\
		src/main.c	\

INCLUDES = minirt.h

SRCO = $(SRC:.c=.o)

FLG = -Wall -Werror -Wextra -g3 -fsanitize=address
CC = gcc

LIB = libft/libft.a
MLX = mlx/libmlx.a

all: $(NAME)
bonus: $(NAME)

%.o: %.c
	$(CC) $(FLG) -c $^ -o $@

$(NAME): $(SRCO) $(LIB) $(MLX)
	$(CC) $(FLG) -framework OpenGL -framework AppKit $^ -o $@

$(LIB):
	make -C libft

$(MLX) :
	make -C mlx

clean:
	make -C libft/ clean
	make -C mlx/ clean
	rm -f $(SRCO)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

re_bonus: fclean

.PHONY: all clean fclean re 
