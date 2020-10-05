/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:05:56 by flolefeb          #+#    #+#             */
/*   Updated: 2020/10/01 12:05:42 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	forward_backward(t_env *env)
{
	if (env->mvt.up == 1)
	{
		if (env->t_map.map[(int)env->t_map.player_pos.y]
		[(int)(env->t_map.player_pos.x + env->ray.dir.x
		* env->ray.speed)] == '0')
			env->t_map.player_pos.x += env->ray.dir.x * env->ray.speed;
		if (env->t_map.map[(int)(env->t_map.player_pos.y + env->ray.dir.y
		* env->ray.speed)][(int)env->t_map.player_pos.x] == '0')
			env->t_map.player_pos.y += env->ray.dir.y * env->ray.speed;
	}
	else if (env->mvt.dwn == 1)
	{
		if (env->t_map.map[(int)env->t_map.player_pos.y]
		[(int)(env->t_map.player_pos.x - env->ray.dir.x
		* env->ray.speed)] == '0')
			env->t_map.player_pos.x -= env->ray.dir.x * env->ray.speed;
		if (env->t_map.map[(int)(env->t_map.player_pos.y - env->ray.dir.y
		* env->ray.speed)][(int)env->t_map.player_pos.x] == '0')
			env->t_map.player_pos.y -= env->ray.dir.y * env->ray.speed;
	}
}

void	side(t_env *env)
{
	if (env->mvt.side_r == 1)
	{
		if (env->t_map.map[(int)(env->t_map.player_pos.y + env->ray.dir.x
		* env->ray.speed)][(int)(env->t_map.player_pos.x)] == '0')
			env->t_map.player_pos.y -= -env->ray.dir.x * env->ray.speed;
		if (env->t_map.map[(int)(env->t_map.player_pos.y)]
		[(int)(env->t_map.player_pos.x
		- env->ray.dir.y * env->ray.speed)] == '0')
			env->t_map.player_pos.x -= env->ray.dir.y * env->ray.speed;
	}
	if (env->mvt.side_l == 1)
	{
		if (env->t_map.map[(int)(env->t_map.player_pos.y - env->ray.dir.x
		* env->ray.speed)][(int)(env->t_map.player_pos.x)] == '0')
			env->t_map.player_pos.y += -env->ray.dir.x * env->ray.speed;
		if (env->t_map.map[(int)(env->t_map.player_pos.y)]
		[(int)(env->t_map.player_pos.x
		+ env->ray.dir.y * env->ray.speed)] == '0')
			env->t_map.player_pos.x += env->ray.dir.y * env->ray.speed;
	}
}

void	rotate_left(t_env *env)
{
	env->ray.old_dir.x = env->ray.dir.x;
	env->ray.dir.x = env->ray.dir.x * cos(-env->ray.speed)
		- env->ray.dir.y * sin(-env->ray.speed);
	env->ray.dir.y = env->ray.old_dir.x * sin(-env->ray.speed)
		+ env->ray.dir.y * cos(-env->ray.speed);
	env->ray.old_plane.x = env->ray.plane.x;
	env->ray.plane.x = env->ray.plane.x * cos(-env->ray.speed)
		- env->ray.plane.y * sin(-env->ray.speed);
	env->ray.plane.y = env->ray.old_plane.x * sin(-env->ray.speed)
		+ env->ray.plane.y * cos(-env->ray.speed);
}

void	rotate_right(t_env *env)
{
	env->ray.old_dir.x = env->ray.dir.x;
	env->ray.dir.x = env->ray.dir.x * cos(env->ray.speed)
	- env->ray.dir.y * sin(env->ray.speed);
	env->ray.dir.y = env->ray.old_dir.x * sin(env->ray.speed)
	+ env->ray.dir.y * cos(env->ray.speed);
	env->ray.old_plane.x = env->ray.plane.x;
	env->ray.plane.x = env->ray.plane.x * cos(env->ray.speed)
	- env->ray.plane.y * sin(env->ray.speed);
	env->ray.plane.y = env->ray.old_plane.x * sin(env->ray.speed)
	+ env->ray.plane.y * cos(env->ray.speed);
}

void	moves(t_env *env)
{
	if (env->mvt.up == 1 || env->mvt.dwn == 1)
		forward_backward(env);
	if (env->mvt.lft == 1)
		rotate_left(env);
	if (env->mvt.rgt == 1)
		rotate_right(env);
	if (env->mvt.side_r == 1 || env->mvt.side_l == 1)
		side(env);
}
