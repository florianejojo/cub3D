/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:05:30 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 15:03:45 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_elems(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (i <= env->t_map.nb_lines && (env->t_check.R != 1
		|| env->t_check.F != 1 || env->t_check.C != 1))
	{
		if (env->t_map.map[i])
		{
			j = skip_wsp(i, 0, env);
			if (elems(i, j, env) != SUCCESS)
				return (INVALID_ELEMENTS);
		}
		i++;
	}
	env->t_map.i = i;
	if (env->t_check.R != 1 || env->t_check.F != 1 || env->t_check.C != 1)
		return (INVALID_ELEMENTS);
	return (SUCCESS);
}

int		elems(int i, int j, t_env *env)
{
	if ((env->t_map.map[i][j] == 'R' && env->t_check.R != 0)
		|| (env->t_map.map[i][j] == 'F' && env->t_check.F != 0)
		|| (env->t_map.map[i][j] == 'C' && env->t_check.C != 0))
		return (INVALID_ELEMENTS);
	else if (env->t_map.map[i][j] == 'R')
		env->t_check.R = 1;
	else if (env->t_map.map[i][j] == 'F')
		env->t_check.F = 1;
	else if (env->t_map.map[i][j] == 'C')
		env->t_check.C = 1;
	return (SUCCESS);
}

void	find_end_line(int i, int j, t_env *env)
{
	while (i < env->t_map.nb_lines)
		i++;
	while (env->t_map.start_line != 0 && env->t_map.end_line == 0
		&& i > env->t_map.i)
	{
		if (env->t_map.map[i])
		{
			j = skip_wsp(i, 0, env);
			if (env->t_map.map[i][j])
				env->t_map.end_line = i;
		}
		i--;
	}
}

int		find_start_end_line(t_env *env)
{
	int j;
	int i;

	j = 0;
	i = env->t_map.i;
	while (i <= env->t_map.nb_lines && env->t_map.start_line == 0)
	{
		if (env->t_map.map[i])
		{
			j = skip_wsp(i, 0, env);
			if (env->t_map.map[i][j])
				env->t_map.start_line = i;
		}
		i++;
	}
	find_end_line(i, j, env);
	if (env->t_map.start_line == 0 || env->t_map.end_line == 0
		|| env->t_map.i == 0)
		return (ERROR_START_END);
	return (SUCCESS);
}

int		check_map(t_env *env)
{
	int		i;

	if ((env->error = check_elems(env)) != SUCCESS)
		return (env->error);
	if ((env->error = find_start_end_line(env)) != SUCCESS)
		return (env->error);
	i = env->t_map.start_line;
	env->j = skip_wsp(i, 0, env);
	while (i <= env->t_map.end_line)
	{
		if (env->t_map.map[i] && env->t_map.map[i][env->j]
			&& line_closed(i, env->t_map.map[i], env) != SUCCESS)
			return (LINE_NOT_CLOSED);
		while (env->t_map.map[i] && env->t_map.map[i][env->j])
		{
			if ((env->error = check_char(i, env->j, env)) != SUCCESS)
				return (env->error);
			env->j++;
		}
		i++;
		env->j = skip_wsp(i, 0, env);
	}
	if (env->t_map.player_dir == 0)
		return (NO_PLAYER_POS);
	return (SUCCESS);
}
