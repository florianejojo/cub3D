# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flolefeb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 15:33:01 by flolefeb          #+#    #+#              #
#    Updated: 2020/02/25 18:25:08 by flolefeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LINUX		= no

ifeq ($(LINUX), yes)
	MLX_FLAGS	= -lXext -lX11 -lm -lbsd
	MLX_PATH	= ./minilibx-linux/
	
else 
	MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit
	MLX_PATH	= ./minilibx_opengl_20191021/
endif


NAME		=	cub3D

LIBFT_PATH	=	./libft/ #dans cub3d la libft doit être dans un dossier à la racine donc juste ./libft

CC			=	clang

SRCS		=	./srcs/cub3d.c \
				./srcs/check_map.c \
				./srcs/check_map2.c \
				./srcs/print_error.c \
				./srcs/treat_file.c \
				./srcs/treat_file_utils.c \
				./srcs/pars_map.c \
				./srcs/pars_map2.c \
				./srcs/ft_split_cub.c \
				./srcs/init_raycasting.c \
				./srcs/pick_color_and_draw.c \
				./srcs/raycasting.c \
				./srcs/raycasting_utils.c \
				./srcs/calc_data_raycasting_2.c \
				./srcs/calc_data_raycasting.c \
				./srcs/moves.c \
				./srcs/add_sprites.c \
				./srcs/add_sprites2.c \
				./srcs/save.c \
				./srcs/quit_and_free.c \

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

HEADER		=	includes/cub3d.h

all			:	$(NAME)

$(NAME) 	:	$(OBJS)
				make -C $(MLX_PATH)
				make -C $(LIBFT_PATH)
				${CC} -fsanitize=address -g3 ${CFLAGS} $(MLX_FLAGS) $(MLX_PATH)*.a ./libft/libft.a $^ -o $@
				printf "\033[32m$@ is ready ! \n\033[0m"
				#cp $(MLX_PATH)*.a /usr/local/lib/


$(OBJS)		:	%.o:%.c ${HEADER}
				${CC} ${CFLAGS} -c $< -o $@

clean		:	
				make clean -C $(LIBFT_PATH) 
				rm -rf $(OBJS)

fclean		:	clean
				make fclean -C $(LIBFT_PATH)
				rm -rf $(NAME)

re			:	fclean all