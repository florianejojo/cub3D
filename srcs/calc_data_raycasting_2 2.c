/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_data_raycasting_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:43:52 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 11:06:32 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_draw_infos(t_env *env)
{
	env->ray.lineheight = fabs(env->t_map.res.height
		/ env->ray.perpwalldist);
	env->ray.drawstart = (-1 * env->ray.lineheight) / 2
		+ env->t_map.res.height / 2;
	if (env->ray.drawstart < 0)
		env->ray.drawstart = 0;
	env->ray.drawend = env->ray.lineheight / 2
		+ env->t_map.res.height / 2;
	if (env->ray.drawend >= env->t_map.res.height)
		env->ray.drawend = env->t_map.res.height - 1;
	env->check_calc = env->check_calc + 1;
}

void	calc_textures_data(t_env *env)
{
	if (env->ray.side == 0)
		env->ray.wall.x = env->t_map.player_pos.y
			+ env->ray.perpwalldist * env->ray.raydir.y;
	else
		env->ray.wall.x = env->t_map.player_pos.x + env->ray.perpwalldist
			* env->ray.raydir.x;
	env->ray.wall.x -= floor(env->ray.wall.x);
	env->ray.tex.x = (int)(env->ray.wall.x * (double)(env->tex_width));
	if ((env->ray.side <= 0 && env->ray.raydir.x > 0) || (env->ray.side > 1
		&& env->ray.raydir.y < 0))
		env->ray.tex.x = env->tex_width - env->ray.tex.x - 1;
	env->ray.tex_step = 1.0 * env->tex_height / env->ray.lineheight;
	env->ray.tex_pos = (env->ray.drawstart - env->t_map.res.height / 2 +
		env->ray.lineheight / 2) * env->ray.tex_step;
}
