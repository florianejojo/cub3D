/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:06:35 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/18 14:06:38 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/cub3d.h"

void		set_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

// t_img *new_image(t_env *env) //int width, int height)
// {
// 	t_img *img;

// 	if (!(img = (t_img *)malloc(sizeof(t_img))))
// 		return (NULL);
// 	if (!(img->ptr = mlx_new_image(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height)))
// 		return (NULL);
// 	if (!(img->addr = (int *)mlx_get_data_addr(img->ptr, &img->bits_pp, &img->line_length, &img->endian)))
// 		return (NULL);
// 	return (img);
// }

t_img *new_image(t_env *env, char *file) //int width, int height)
{
	t_img *img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	if (!file)
	{
		if (!(img->ptr = mlx_new_image(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height)))
			return (NULL);
	}
	else
	{
		if (!(img->ptr = mlx_xpm_file_to_image(env->mlx_ptr, file, &env->tex_width, &env->tex_height)))
			return (NULL);
	}
	if (!(img->addr = (int *)mlx_get_data_addr(img->ptr, &img->bits_pp, &img->line_length, &img->endian)))
		return (NULL);
	return (img);
}

	// t_tex *new_texture(t_env *env, char *file)
	// {
	// 	t_tex *img_tex;

	// 	env->tex_height = TEXHEIGHT;
	// 	env->tex_width = TEXWIDTH;

	// 	if (!(img_tex = (t_tex *)malloc(sizeof(t_tex))))
	// 		return (NULL);
	// 	if (!(img_tex->ptr = mlx_xpm_file_to_image(env->mlx_ptr, file, &env->tex_width, &env->tex_height)))
	// 		return (NULL);
	// 	if (!(img_tex->addr = (int *)mlx_get_data_addr(img_tex->ptr, &img_tex->bits_pp, &img_tex->line_length, &img_tex->endian)))
	// 		return (NULL);
	// 	return (img_tex);
	// }

	void free_img(t_img *img, t_env *env)
	{
		if (img)
		{
			mlx_destroy_image(env->mlx_ptr, img->ptr);
			free(img);
		}
	}

	void free_textures(t_env *env)
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

	void free_all(t_env * env)
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
		// return (SUCCESS);
	}