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

NAME		=	cub3D

LIBFT_PATH	=	libft

CC			=	clang

SRCS		=	srcs/cub3d.c \
				srcs/check_map.c \
				srcs/check_map2.c \
				srcs/print_error.c \
				srcs/treat_file.c \
				srcs/treat_file_utils.c \
				srcs/pars_map.c \
				srcs/pars_map2.c \
				srcs/ft_split_cub.c \
				srcs/init_raycasting.c \
				srcs/pick_color_and_draw.c \
				srcs/raycasting.c \
				srcs/raycasting_utils.c \
				srcs/calc_data_raycasting_2.c \
				srcs/calc_data_raycasting.c \
				srcs/moves.c \
				srcs/add_sprites.c \
				srcs/add_sprites2.c \
				srcs/save.c \
				srcs/quit_and_free.c \

LIBFT		=	libft/libft.a

MLX_MAC		=	-lmlx -framework OpenGL -framework AppKit

MLX_LINUX	=	-lmlx -lXext -lX11 -lm -lbsd

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

HEADER		=	includes/cub3d.h

all			:	$(NAME)

$(NAME) 	:	$(OBJS)
				make -C $(LIBFT_PATH)
				${CC} ${CFLAGS} -fsanitize=address -g3 -I ${HEADER} ${OBJS} $(LIBFT) $(MLX_MAC) -o ${NAME}
				printf "\033[32m$@ is ready ! \n\033[0m"

$(OBJS)		:	%.o:%.c ${HEADER}
				${CC} ${CFLAGS} -I ${HEADER} -c $< -o $@


clean		:	
				make clean -C $(LIBFT_PATH) 
				rm -rf $(OBJS)

fclean		:	clean
				make fclean -C $(LIBFT_PATH)
				rm -rf $(NAME)

re			:	fclean all
