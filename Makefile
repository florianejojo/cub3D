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


LINUX			= no

ifeq ($(LINUX), yes)
MLX_FLAGS		= -lXext -lX11 -lm -lbsd
MLX_PATH		= ./minilibx-linux/
else 
MLX_FLAGS		= -lmlx -framework OpenGL -framework AppKit
MLX_PATH		= ./minilibx_opengl_20191021/
endif

NAME			=	cub3D

LIBFT_PATH		=	./libft/

CC				=	clang

SRCS			=	./srcs/cub3d.c \
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

SRCS_BONUS	=		./srcs_bonus/cub3d.c \
					./srcs_bonus/check_map.c \
					./srcs_bonus/check_map2.c \
					./srcs_bonus/print_error.c \
					./srcs_bonus/treat_file.c \
					./srcs_bonus/treat_file_utils.c \
					./srcs_bonus/pars_map.c \
					./srcs_bonus/pars_map2.c \
					./srcs_bonus/ft_split_cub.c \
					./srcs_bonus/init_raycasting.c \
					./srcs_bonus/pick_color_and_draw.c \
					./srcs_bonus/raycasting.c \
					./srcs_bonus/raycasting_utils.c \
					./srcs_bonus/calc_data_raycasting_2.c \
					./srcs_bonus/calc_data_raycasting.c \
					./srcs_bonus/moves.c \
					./srcs_bonus/add_sprites.c \
					./srcs_bonus/add_sprites2.c \
					./srcs_bonus/save.c \
					./srcs_bonus/quit_and_free.c \
					./srcs_bonus/floor_and_ceiling_textures.c \

OBJS			=	$(SRCS:.c=.o)

OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)	

INCLUDES		=	./includes

INCLUDES_BONUS 	=	./includes_bonus

CFLAGS			=	-Wall -Wextra -Werror

HEADER			=	./includes/cub3d.h

HEADER_BONUS	=	./includes_bonus/cub3d.h 

all				:	$(NAME)



$(NAME) 		:	$(OBJS)
					make -C $(MLX_PATH)
					make -C $(LIBFT_PATH)
					${CC} ${CFLAGS} -I $(INCLUDES) $^ $(MLX_FLAGS) -o $@ ./minilibx_opengl_20191021/libmlx.a  ./libft/libft.a
					printf "cub3D is ready ! \n\033[0m"


$(OBJS)			:	%.o:%.c ${HEADER}
					${CC} ${CFLAGS} -c $< -o $@

$(OBJS_BONUS)	:	%.o:%.c ${HEADER_BONUS}
					${CC} ${CFLAGS} -c $< -o $@

bonus			:	$(OBJS_BONUS)
					make -C $(MLX_PATH)
					make -C $(LIBFT_PATH)
					${CC} ${CFLAGS} -fsanitize=address -g3 -I $(INCLUDES_BONUS) $(OBJS_BONUS) $(MLX_FLAGS) -o $(NAME) ./minilibx-linux/libmlx.a  ./libft/libft.a
					printf "Bonus is ready ! \n\033[0m"	

clean			:	
					make clean -C $(LIBFT_PATH) 
					rm -rf $(OBJS) $(OBJS_BONUS)

fclean			:	clean
					make fclean -C $(LIBFT_PATH)
					rm -rf $(NAME)

re				:	fclean all