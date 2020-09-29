/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_data_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:09:21 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/29 18:53:25 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_textures_data(t_env *env);
void	calc_draw_infos(t_env *env);

void	init_vectors(t_env *env, int x)
{
	env->ray.camera = 2 * x / (double)env->t_map.res.width - 1;
	env->ray.raydir.x = env->ray.dir.x + env->ray.plane.x * env->ray.camera;
	env->ray.raydir.y = env->ray.dir.y + env->ray.plane.y * env->ray.camera;
	env->ray.map.x = (int)env->t_map.player_pos.x;
	env->ray.map.y = (int)env->t_map.player_pos.y;
	env->ray.deltadist.x = sqrt(1 + (env->ray.raydir.y * env->ray.raydir.y) /
		(env->ray.raydir.x * env->ray.raydir.x));
	env->ray.deltadist.y = sqrt(1 + (env->ray.raydir.x * env->ray.raydir.x) /
		(env->ray.raydir.y * env->ray.raydir.y));
	env->ray.hit = 0;
}

void	calc_step(t_env *env)
{
	if (env->ray.raydir.x < 0)
	{
		env->ray.step.x = -1;
		env->ray.sidedist.x = (env->t_map.player_pos.x - env->ray.map.x)
		* env->ray.deltadist.x;
	}
	else
	{
		env->ray.step.x = 1;
		env->ray.sidedist.x = (env->ray.map.x + 1.0 - env->t_map.player_pos.x)
		* env->ray.deltadist.x;
	}
	if (env->ray.raydir.y < 0)
	{
		env->ray.step.y = -1;
		env->ray.sidedist.y = (env->t_map.player_pos.y - env->ray.map.y)
		* env->ray.deltadist.y;
	}
	else
	{
		env->ray.step.y = 1;
		env->ray.sidedist.y = (env->ray.map.y + 1.0 - env->t_map.player_pos.y)
		* env->ray.deltadist.y;
	}
	env->check_calc = env->check_calc + 1;
}

void	perform_dda(t_env *env)
{
	while (env->ray.hit == 0)
	{
		if (env->ray.sidedist.x < env->ray.sidedist.y)
		{
			env->ray.sidedist.x += env->ray.deltadist.x;
			env->ray.map.x += env->ray.step.x;
			env->ray.side = 0;
		}
		else
		{
			env->ray.sidedist.y += env->ray.deltadist.y;
			env->ray.map.y = env->ray.map.y + env->ray.step.y;
			env->ray.side = 1;
		}
		if (env->t_map.map[env->ray.map.y][env->ray.map.x] != '0'
				&& env->t_map.map[env->ray.map.y][env->ray.map.x] != '2')
			env->ray.hit = 1;
	}
}

void	calc_perpwalldist(t_env *env)
{
	if (env->ray.side == 0)
		env->ray.perpwalldist = fabs((env->ray.map.x - env->t_map.player_pos.x
			+ (1 - env->ray.step.x) / 2) / env->ray.raydir.x);
	else
		env->ray.perpwalldist = fabs((env->ray.map.y - env->t_map.player_pos.y
			+ (1 - env->ray.step.y) / 2) / env->ray.raydir.y);
}

int		calc_data_raycasting(t_env *env, int x)
{
	init_vectors(env, x);
	calc_step(env);
	perform_dda(env);
	calc_perpwalldist(env);
	calc_draw_infos(env);
	calc_textures_data(env);
	return (SUCCESS);
}
