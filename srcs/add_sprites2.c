/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sprites2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:32:59 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 17:54:22 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	count_sprites(t_env *env)
{
	int i;
	int j;

	env->sprites.nb = 0;
	i = env->t_map.start_line;
	j = 0;
	while (i <= env->t_map.end_line)
	{
		while (env->t_map.map[i][j])
		{
			if (env->t_map.map[i][j] == '2')
			{
				env->sprites.nb += 1;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	init_calc_sprites(t_env *env, int i)
{
	env->sprites.x = env->sprite_pos_x[env->order[i]] - env->t_map.player_pos.x;
	env->sprites.y = env->sprite_pos_y[env->order[i]] - env->t_map.player_pos.y;
	env->sprites.inv_det = 1.0 / (env->ray.plane.x * env->ray.dir.y
		- env->ray.dir.x * env->ray.plane.y);
	env->sprites.transform.x = env->sprites.inv_det * (env->ray.dir.y
		* env->sprites.x - env->ray.dir.x * env->sprites.y);
	env->sprites.transform.y = env->sprites.inv_det * (-env->ray.plane.y
		* env->sprites.x + env->ray.plane.x * env->sprites.y);
	env->sprites.screen.x = (int)((env->t_map.res.width / 2)
		* (1 + env->sprites.transform.x / env->sprites.transform.y));
}

void	calc_size_screen_sprites(t_env *env)
{
	env->sprites.height = abs((int)(env->t_map.res.height
		/ env->sprites.transform.y));
	env->sprites.drawstart.y = -env->sprites.height / 2
		+ env->t_map.res.height / 2;
	if (env->sprites.drawstart.y < 0)
		env->sprites.drawstart.y = 0;
	env->sprites.drawend.y = env->sprites.height / 2
		+ env->t_map.res.height / 2;
	if (env->sprites.drawend.y >= env->t_map.res.height)
		env->sprites.drawend.y = env->t_map.res.height - 1;
	env->sprites.width = abs((int)(env->t_map.res.height
		/ env->sprites.transform.y));
	env->sprites.drawstart.x = -env->sprites.width / 2 + env->sprites.screen.x;
	if (env->sprites.drawstart.x < 0)
		env->sprites.drawstart.x = 0;
	env->sprites.drawend.x = env->sprites.width / 2 + env->sprites.screen.x;
	if (env->sprites.drawend.x >= env->t_map.res.width)
		env->sprites.drawend.x = env->t_map.res.width - 1;
}

void	draw_sprites_2(t_env *env, int y, int d, int stripe)
{
	d = (y) * 256 - env->t_map.res.height * 128
		+ env->sprites.height * 128;
	env->sprites.tex.y = ((d * env->tex_height)
		/ env->sprites.height) / 256;
	env->sprites.color = env->img_tex_S->addr[env->tex_width
		* env->sprites.tex.y
		+ env->sprites.tex.x];
	if ((env->sprites.color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(env, stripe, y, env->sprites.color);
}

void	draw_sprites(t_env *env)
{
	int stripe;
	int y;
	int d;

	d = 0;
	stripe = env->sprites.drawstart.x;
	while (stripe < env->sprites.drawend.x)
	{
		env->sprites.tex.x = (int)(256 * (stripe - (-env->sprites.width
		/ 2 + env->sprites.screen.x)) * env->tex_width
		/ env->sprites.width) / 256;
		if (env->sprites.transform.y > 0 && stripe > 0 && stripe
		< env->t_map.res.width
			&& env->sprites.transform.y < env->zbuffer[stripe])
		{
			y = env->sprites.drawstart.y;
			while (y < env->sprites.drawend.y)
				draw_sprites_2(env, y++, d, stripe);
		}
		stripe++;
	}
}
