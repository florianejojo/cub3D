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

LIBFT_PATH	=	./libft/ #dans cub3d la libft doit être dans un dossier à la racine donc juste ./libft

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
				libft/ft_bzero.c \
				libft/ft_charset.c \
				libft/ft_putstr_fd.c \
				libft/ft_strlen.c \
				libft/ft_substr.c \
				libft/ft_putchar_fd.c \

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

HEADER		=	includes/cub3d.h

all			:	$(NAME)

$(NAME) 	:	$(OBJS)
				${CC} ${CFLAGS} -I ${HEADER} ${OBJS} -lmlx -framework OpenGL -framework AppKit -o ${NAME}
				printf "\033[32m$@ is ready ! \n\033[0m"


${OBJS}		: 	%.o: %.c ${HEADER}
				${CC} ${CFLAGS} -I ${HEADER} -c $< -o $@

clean		:	
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all
