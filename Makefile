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

NAME		=	libftprintf.a

LIBFT_PATH	=	srcs/libft/ #dans cub3d la libft doit être dans un dossier à la racine donc juste ./libft

CC			=	gcc

SRCS		=	srcs/ft_printf.c \
				srcs/ft_print_c.c \
				srcs/ft_print_s.c \
				srcs/ft_print_d.c \
				srcs/ft_print_p.c \
				srcs/ft_init_stru.c \
				srcs/ft_itoa_base.c \
				srcs/ft_printf_utils.c \
				srcs/ft_print_per.c \

OBJS		=	$(SRCS:.c=.o)

FLAGS		=	-c -Wall -Wextra -Werror

HEADER		=	includes/ft_printf.h

all			:	$(NAME)

$(NAME) 	:	$(HEADER) $(OBJS)
				make -C $(LIBFT_PATH)
				cp $(LIBFT_PATH)/libft.a $(NAME)
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

