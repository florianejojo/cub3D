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

#include "../includes_bonus/cub3d.h"

void	free_struct_img(t_img *img, t_env *env)
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
		free_struct_img(env->img_tex_NO, env);
	if (env->img_tex_SO)
		free_struct_img(env->img_tex_SO, env);
	if (env->img_tex_WE)
		free_struct_img(env->img_tex_WE, env);
	if (env->img_tex_EA)
		free_struct_img(env->img_tex_EA, env);
	if (env->img_tex_S)
		free_struct_img(env->img_tex_S, env);
	// if (env->bonus->ceiling_img)
	// 	free_struct_img(env->bonus->ceiling_img, env);
	// if (env->bonus->floor_img)
	// 	free_struct_img(env->bonus->ceiling_img, env);
}

void	free_dtab(t_env *env, char **tab)
{
	int i;

	i = 0;
	while (i <= env->t_map.nb_lines)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
}

void	free_tabs(t_env *env)
{
	if (env->t_textures_path.NO)
		free(env->t_textures_path.NO);
	if (env->t_textures_path.SO)
		free(env->t_textures_path.SO);
	if (env->t_textures_path.WE)
		free(env->t_textures_path.WE);
	if (env->t_textures_path.EA)
		free(env->t_textures_path.EA);
	if (env->t_textures_path.S)
		free(env->t_textures_path.S);
	if (env->t_map.map)
		free(env->t_map.map);
}
void	free_all(t_env *env)
{
	if (env)
		free_textures(env);
	if (env->t_map.map)
		free_dtab(env, env->t_map.map);
	if (env)
		free_tabs(env);
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
}

void	free_sprites(t_env *env)
{
	if (env->sprite_pos_x)
		free(env->sprite_pos_x);
	if (env->sprite_pos_y)
		free(env->sprite_pos_y); 
}

int		quit(t_env *env)
{
	free_all(env);
	if (env->win_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	// if (env->img)
	// {
	// 	mlx_destroy_image(env->mlx_ptr, env->img->ptr);
	// 	free(env->img);
	// }
	if (env->mlx_ptr)
		free(env->mlx_ptr);
	if (env)
		free(env);
	exit(1);
	return (SUCCESS);
}