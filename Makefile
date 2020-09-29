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

NAME		=	Cub3d

LIBFT_PATH	=	libft #dans cub3d la libft doit être dans un dossier à la racine donc juste ./libft

OBJS_PATH	=	objs/

CC			=	clang

SRCS		=	main.c \
				srcs/check_map.c \
				srcs/print_error.c \
				srcs/init_map.c \
				srcs/init_map_utils.c \
				srcs/pars_map.c \
				srcs/pars_map2.c \
				srcs/ft_split_cub.c \
				srcs/init_raycasting.c \
				srcs/raycasting.c \
				srcs/raycasting_utils.c \
				srcs/calc_data_raycasting_2.c \
				srcs/calc_data_raycasting.c \
				srcs/moves.c \
				srcs/sprites.c \
				srcs/create_rgb.c \
				srcs/save.c \

LIBS		=	libft/libft.a -lmlx -framework OpenGL -framework AppKit

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

HEADER		=	includes/cub3d.h

all			:	$(NAME)

$(NAME) 	:	$(OBJS) 
				make -C $(LIBFT_PATH)
				${CC} ${CFLAGS} -fsanitize=address -g3 -I ${HEADER} ${OBJS} $(LIBS) -o ${NAME}
				printf "\033[32m$@ is ready ! \n\033[0m"

%.o			:	%.c ${HEADER}
				${CC} ${CFLAGS} -I ${HEADER} -c $< -o $@


clean		:	
				make clean -C $(LIBFT_PATH) 
				rm -rf $(OBJS)

fclean		:	clean
				make fclean -C $(LIBFT_PATH) 
				rm -rf $(NAME)

re			:	fclean all
