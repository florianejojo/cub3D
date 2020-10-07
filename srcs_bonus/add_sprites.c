/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:32:45 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 17:41:36 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	stock_sprites_pos(t_env *env)
{
	int i;
	int j;
	int nb;

	nb = 0;
	i = env->t_map.start_line;
	j = 0;
	while (i <= env->t_map.end_line)
	{
		while (env->t_map.map[i][j] && nb < env->sprites.nb)
		{
			if (env->t_map.map[i][j] == '2')
			{
				env->sprite_pos_x[nb] = j + 0.5;
				env->sprite_pos_y[nb] = i + 0.5;
				nb++;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	make_tab_distance(t_env *env)
{
	int i;

	i = 0;
	while (i < env->sprites.nb)
	{
		env->order[i] = i;
		env->distance[i] = ((env->t_map.player_pos.x - env->sprite_pos_x[i])
		* (env->t_map.player_pos.x - env->sprite_pos_x[i])
		+ (env->t_map.player_pos.y - env->sprite_pos_y[i])
		* (env->t_map.player_pos.y - env->sprite_pos_y[i]));
		i++;
	}
}

void	sort_tab(t_env *env)
{
	int		i;
	int		temp;
	double	temp2;

	i = 0;
	while (i < env->sprites.nb - 1)
	{
		if (env->distance[i] < env->distance[i + 1])
		{
			temp2 = env->distance[i + 1];
			env->distance[i + 1] = env->distance[i];
			env->distance[i] = temp2;
			temp = env->order[i + 1];
			env->order[i + 1] = env->order[i];
			env->order[i] = temp;
			i = 0;
		}
		else
			i++;
	}
}

int		add_sprites(t_env *env)
{
	int i;

	stock_sprites_pos(env);
	make_tab_distance(env);
	sort_tab(env);
	i = 0;
	while (i < env->sprites.nb)
	{
		init_calc_sprites(env, i);
		calc_size_screen_sprites(env);
		draw_sprites(env);
		i++;
	}
	
	return (SUCCESS);
}
