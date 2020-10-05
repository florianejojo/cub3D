/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_color_and_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:12:25 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 18:10:44 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
	env->img->addr[(y * env->t_map.res.width + x)] = color;
}

void	pick_color(t_env *env)
{
	env->ray.color = 0;
	if (env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x]
		&& env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x] == '1')
	{
		if (env->ray.side == 0)
		{
			if (env->ray.step.x < 0)
				env->ray.color = env->img_tex_WE->addr[(env->tex_height
					* env->ray.tex.y + env->ray.tex.x)];
			else
				env->ray.color = env->img_tex_EA->addr[(env->tex_height
					* env->ray.tex.y + env->ray.tex.x)];
		}
		else
		{
			if (env->ray.step.y > 0)
				env->ray.color = env->img_tex_SO->addr[(env->tex_height
					* env->ray.tex.y + env->ray.tex.x)];
			else
				env->ray.color = env->img_tex_NO->addr[(env->tex_height
					* env->ray.tex.y + env->ray.tex.x)];
			env->ray.color = (env->ray.color >> 1) & 8355711;
		}
	}
}

void	draw_line(t_env *env, int x, int drawstart, int drawend)
{
	int y;

	y = 0;
	while (y < drawstart)
	{
		my_mlx_pixel_put(env, x, y, create_rgb(env->t_colors.rgb_C.r,
			env->t_colors.rgb_C.g, env->t_colors.rgb_C.b));
		y++;
	}
	while (y <= drawend)
	{
		env->ray.tex.y = (int)env->ray.tex_pos & (env->tex_height - 1);
		env->ray.tex_pos += env->ray.tex_step;
		pick_color(env);
		my_mlx_pixel_put(env, x, y, env->ray.color);
		y++;
	}
	while (y < env->t_map.res.height)
	{
		my_mlx_pixel_put(env, x, y, create_rgb(env->t_colors.rgb_F.r,
			env->t_colors.rgb_F.g, env->t_colors.rgb_F.b));
		y++;
	}
}
