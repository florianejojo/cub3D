/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:10:50 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 17:20:47 by flolefeb         ###   ########.fr       */
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


void	free_textures(t_env *env)
{
	if (env->img_tex_NO)
		free_img(env->img_tex_NO, env);
	if (env->img_tex_SO)
		free_img(env->img_tex_SO, env);
	if (env->img_tex_WE)
		free_img(env->img_tex_WE, env);
	if (env->img_tex_EA)
		free_img(env->img_tex_EA, env);
	if (env->img_tex_S)
		free_img(env->img_tex_S, env);
}

void	free_all(t_env *env)
{
	free_textures(env);
	if (env->t_map.map)
		free(env->t_map.map);
	if (env->zbuffer)
		free(env->zbuffer);
	if (env->order)
		free(env->order);
	if (env->distance)
		free(env->distance);
	if (env->sprite_pos_x)
		free(env->sprite_pos_x);
	if (env->sprite_pos_y)
		free(env->sprite_pos_y);
	if (env)
		free(env);
}


int		quit(t_env *env)
{
	free_all(env);
	if (env->win_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->img)
	{
		mlx_destroy_image(env->mlx_ptr, env->img->ptr);
		free(env->img);
	}
	env->img = NULL;
	if (env->mlx_ptr)
		free(env->mlx_ptr);
	exit(1);
	return (SUCCESS);
}