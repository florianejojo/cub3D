/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:27:18 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 17:46:48 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		init_dir_plane(t_env *env)
{
	if (env->t_map.player_dir == 'N')
	{
		env->ray.dir.y = -1;
		env->ray.plane.x = 0.80;
	}
	else if (env->t_map.player_dir == 'S')
	{
		env->ray.dir.y = 1;
		env->ray.plane.x = -0.80;
	}
	else if (env->t_map.player_dir == 'E')
	{
		env->ray.dir.x = 1;
		env->ray.plane.y = 0.80;
	}
	else if (env->t_map.player_dir == 'W')
	{
		env->ray.dir.x = -1;
		env->ray.plane.y = -0.80;
	}
	return (SUCCESS);
}

int		init_textures(t_env *env)
{
	env->tex_height = 0;
	env->tex_width = 0;
	if ((env->img_tex_NO = new_image(env, env->t_textures_path.NO)) == NULL)
		return (WRONG_TEX);
	if ((env->img_tex_SO = new_image(env, env->t_textures_path.SO)) == NULL)
		return (WRONG_TEX);
	if ((env->img_tex_WE = new_image(env, env->t_textures_path.WE)) == NULL)
		return (WRONG_TEX);
	if ((env->img_tex_EA = new_image(env, env->t_textures_path.EA)) == NULL)
		return (WRONG_TEX);
	if ((env->img_tex_S = new_image(env, env->t_textures_path.S)) == NULL)
		return (WRONG_TEX);
	return (SUCCESS);
}

int		init_sprites(t_env *env)
{
	if (!(env->zbuffer = malloc(sizeof(double) * env->t_map.res.width)))
		return (MALLOC_FAILED);
	if (!(env->order = (int *)malloc(sizeof(int) * env->sprites.nb)))
		return (MALLOC_FAILED);
	if (!(env->distance = (double *)malloc(sizeof(double) * env->sprites.nb)))
		return (MALLOC_FAILED);
	if (!(env->sprite_pos_x = (double *)malloc(sizeof(double)
	* env->sprites.nb)))
		return (MALLOC_FAILED);
	if (!(env->sprite_pos_y = (double *)malloc(sizeof(double)
	* env->sprites.nb)))
		return (MALLOC_FAILED);
	return (SUCCESS);
}

int		init_raycasting(t_env *env)
{
	int		x;

	x = 0;
	env->ray.speed = 0.1;
	env->ray.map.x = (int)env->t_map.player_pos.x;
	env->ray.map.y = (int)env->t_map.player_pos.y;
	if (!(env->mlx_ptr = mlx_init()))
		return (MLX_FAIL);
	// if (env->img == NULL)
	// 	env->img = new_image(env, NULL);
	if (!(env->img = (t_img *)malloc(sizeof(t_img))))
		return (IMG_FAIL);
	if (!(env->img->ptr = mlx_new_image(env->mlx_ptr,
			env->t_map.res.width, env->t_map.res.height)))
			return (MLX_FAIL);
	if (!(env->img->addr = (unsigned int *)mlx_get_data_addr(env->img->ptr,
		&env->img->bits_pp, &env->img->line_length, &env->img->endian)))
		return (MLX_FAIL);
	if ((env->error = init_dir_plane(env)) != SUCCESS)
		return (env->error);
	if ((env->error = init_textures(env)) != SUCCESS)
		return (env->error);
	count_sprites(env);
	if ((env->error = init_sprites(env)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}
