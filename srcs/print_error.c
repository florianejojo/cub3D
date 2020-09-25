/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:06:29 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/25 16:57:12 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/cub3d.h"

int		print_error(int error)
{

	if (error == SUCCESS) // à enlever à la fin
        ft_putstr_fd("SUCCESS\n", 1);
  	else if (error == INVALID_ELEMENTS)
		ft_putstr_fd("Error\n Invalid elements\n", 1);
	else if (error == LINE_NOT_CLOSED)
		ft_putstr_fd("Error\n Line not closed\n", 1);
	else if (error == MAP_NOT_CLOSED)
		ft_putstr_fd("Error\n map not closed\n", 1);
	else if (error == WRONG_CHAR)
		ft_putstr_fd("Error\n Wrong char in the map\n", 1);
	else if (error == INVALID_FILE)
		ft_putstr_fd("Error\n Invalid file extention\n", 1);
	else if (error == FILE_NOT_OPENED)
		ft_putstr_fd("Error\n Fail opening file\n", 1);
	else if (error == NO_PLAYER_POS)
		ft_putstr_fd("Error\n No player position detected\n", 1);
	else if (error == TO_MANY_PLAYER_POS)
		ft_putstr_fd("Error\n Two or more player positions detected\n", 1);
	else if (error == MALLOC_FAILED)
		ft_putstr_fd("Error\n Malloc failed\n", 1);
	else if (error == ERROR_RES)
		ft_putstr_fd("Error\n Resolution\n", 1);
	else if (error == INVALID_TEXTURES)
		ft_putstr_fd("Error\n Textures\n", 1);
	else if (error == ERROR_PARSING)
		ft_putstr_fd("Error\n Parsing\n", 1);
	else if (error == ERROR_COLORS)
		ft_putstr_fd("Error\n Colors\n", 1);
	else if (error == ERROR_START_END)
		ft_putstr_fd("Error\n start or end lines not found\n", 1);
	else if (error == MLX_FAIL)
		ft_putstr_fd("Error\n mlx pb\n", 1);
	else if (error == IMG_FAIL)
		ft_putstr_fd("Error\n img pb\n", 1);
	else if (error == WRONG_TEX)
		ft_putstr_fd("Error\n wrong tex\n", 1);
	else if (error == ERROR_SPRITES)
		ft_putstr_fd("Error\n Sprites\n", 1);
	else if (error == ERROR_SAVE)
		ft_putstr_fd("Error\n File not saved\n", 1);
	return (1);
}