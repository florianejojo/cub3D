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

NAME		=	cub3d.a

LIBFT_PATH	=	libft/ #dans cub3d la libft doit être dans un dossier à la racine donc juste ./libft

CC			=	gcc

SRCS		=	srcs/parsing.c \
				srcs/pars_textures.c \
				srcs/check_map.c \
				srcs/print_error.c \
#%.o: %.c

OBJS		=	$(SRCS:.c=.o)

FLAGS		=	-c -Wall -Wextra -Werror -Imlx -c $< -o $@ #ajouté -Imlx -c $< -o $@ 

HEADER		=	includes/cub3d.h

all			:	$(NAME)

$(NAME) 	:	$(HEADER) $(OBJS)
				make -C $(LIBFT_PATH)
				cp ./libft/libft.a $(NAME)
				$(CC) $(FLAGS) $(SRCS)
				ar -rcs $(NAME) $(OBJS)
				ranlib $(NAME)

clean		:	
				make -C $(LIBFT_PATH) clean
				rm -rf $(OBJS)
				rm -rf *.o

fclean		:	clean
				make -C $(LIBFT_PATH) fclean
				rm -rf $(NAME)

re			:	fclean all

