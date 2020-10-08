/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 10:56:24 by flolefeb          #+#    #+#             */
/*   Updated: 2020/10/01 11:14:07 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

int		key_press(int key, t_env *env)
{
	if (key == KEY_W)
		env->mvt.up = 1;
	if (key == KEY_S)
		env->mvt.dwn = 1;
	if (key == KEY_LEFT)
		env->mvt.lft = 1;
	if (key == KEY_RIGHT)
		env->mvt.rgt = 1;
	if (key == KEY_A)
		env->mvt.side_l = 1;
	if (key == KEY_D)
		env->mvt.side_r = 1;
	if (key == KEY_ESCAPE)
		quit(env);
	return (SUCCESS);
}

int		key_release(int key, t_env *env)
{
	if (key == KEY_W)
		env->mvt.up = 0;
	if (key == KEY_S)
		env->mvt.dwn = 0;
	if (key == KEY_LEFT)
		env->mvt.lft = 0;
	if (key == KEY_RIGHT)
		env->mvt.rgt = 0;
	if (key == KEY_A)
		env->mvt.side_l = 0;
	if (key == KEY_D)
		env->mvt.side_r = 0;
	return (SUCCESS);
}

int		main_loop(t_env *env)
{
	// if (env->img->ptr)
	// 	mlx_destroy_image(env->mlx_ptr, env->img->ptr);
	if (!(env->img->ptr = mlx_new_image(env->mlx_ptr,
			env->t_map.res.width, env->t_map.res.height)))
			return (MLX_FAIL);
	if (!(env->img->addr = (unsigned int *)mlx_get_data_addr(env->img->ptr,
		&env->img->bits_pp, &env->img->line_length, &env->img->endian)))
		return (MLX_FAIL);
	moves(env);
	if ((env->error = draw_floor_and_ceiling(env)) != SUCCESS)
		return (env->error);
	env->line = 0;
	while (env->line <= env->t_map.res.width)
	{
		calc_data_raycasting(env, env->line);
		draw_line(env, env->line, env->ray.drawstart, env->ray.drawend);
		env->zbuffer[env->line] = env->ray.perpwalldist;
		env->line++;
	}
	add_sprites(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img->ptr, 0, 0);
	return (SUCCESS);
}

int		raycasting(t_env *env)
{
	if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width,
		env->t_map.res.height, "Cub3D")))
		return (MLX_FAIL);
	ft_bzero(&env->mvt, sizeof(t_mvt));
	mlx_hook(env->win_ptr, 17, STRUCTURENOTIFYMASK, quit, env);
	mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, env);
	mlx_hook(env->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, env);
	if (main_loop (env) != SUCCESS)
		return (ERROR_COLORS);
	mlx_loop_hook(env->mlx_ptr, main_loop, env);
	mlx_loop(env->mlx_ptr);
	return (SUCCESS);
}
