/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_and_free2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:41:47 by flolefeb          #+#    #+#             */
/*   Updated: 2020/10/09 16:44:45 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_img(t_img *img, t_env *env)
{
	if (img)
	{
		mlx_destroy_image(env->mlx_ptr, img->ptr);
		free(img);
	}
}

void	free_sprites(t_env *env)
{
	if (env->sprite_pos_x)
		free(env->sprite_pos_x);
	if (env->sprite_pos_y)
		free(env->sprite_pos_y);
}
