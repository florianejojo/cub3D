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

CC			=	clang

SRCS		=	main.c \
				srcs/check_map.c \
				srcs/print_error.c \
				srcs/init_map.c \
				srcs/init_map_utils.c \
				srcs/pars_map.c \
				srcs/pars_map2.c \
				srcs/ft_split_cub.c \
				srcs/init_ray.c \
				#srcs/ray.c \#

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

HEADER		=	includes/cub3d.h

mk_libft	:	
				make -C ./libft

all			:	mk_libft
				$(NAME)



$(NAME) 	:	$(OBJS)
				${CC} ${CFLAGS} -I ${HEADER} ${OBJS} libft/libft.a -lmlx -framework OpenGL -framework AppKit -o ${NAME}
				printf "\033[32m$@ is ready ! \n\033[0m"


${OBJS}		: 	%.o: %.c ${HEADER}
				${CC} ${CFLAGS} -I ${HEADER} -c $< -o $@

clean		:	
				make clean -C ./libft
				rm -rf $(OBJS)

fclean		:	clean
				make fclean -C ./libft
				rm -rf $(NAME)

re			:	fclean all

