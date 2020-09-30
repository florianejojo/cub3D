/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:06:17 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 15:22:15 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		pars_resolution(t_env *env, int i, int j)
{
	j = skip_wsp(i, j + 1, env);
	while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
	{
		env->t_map.res.width = env->t_map.res.width * 10
			+ env->t_map.map[i][j] - 48;
		j++;
	}
	j = skip_wsp(i, j, env);
	while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
	{
		env->t_map.res.height = env->t_map.res.height * 10
			+ env->t_map.map[i][j] - 48;
		j++;
	}
	j = skip_wsp(i, j, env);
	if (env->t_map.res.width == 0 || env->t_map.res.height == 0)
		return (ERROR_RES);
	return (SUCCESS);
}

void	ceiling(t_env *env)
{
	env->t_check.C = 1;
	if (k == 'r')
		env->t_colors.rgb_C.r = env->t_colors.rgb_C.r * 10
			+ env->t_map.map[i][j] - 48;
	else if (k == 'g')
		env->t_colors.rgb_C.g = env->t_colors.rgb_C.g * 10
			+ env->t_map.map[i][j] - 48;
	else
		env->t_colors.rgb_C.b = env->t_colors.rgb_C.b * 10
			+ env->t_map.map[i][j] - 48;
}

int		pars_colors_rgb(t_env *env, int i, int j, int k)
{
	if (env->t_map.map[i][skip_wsp(i, 0, env)] == 'F')
	{
		env->t_check.F = 1;
		if (k == 'r')
			env->t_colors.rgb_F.r = env->t_colors.rgb_F.r * 10
				+ env->t_map.map[i][j] - 48;
		else if (k == 'g')
			env->t_colors.rgb_F.g = env->t_colors.rgb_F.g * 10
				+ env->t_map.map[i][j] - 48;
		else
			env->t_colors.rgb_F.b = env->t_colors.rgb_F.b * 10
				+ env->t_map.map[i][j] - 48;
		return (SUCCESS);
	}
	else if (env->t_map.map[i][skip_wsp(i, 0, env)] == 'C')
	{
		ceiling(env);
		return (SUCCESS);
	}
	return (ERROR_COLORS);
}

int		pars_colors(t_env *env, int i, int j)
{
	j = skip_wsp(i, j + 1, env);
	while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j]
		<= '9' && pars_colors_rgb(env, i, j, 'r') == SUCCESS)
		j++;
	j = skip_wsp(i, j, env) + 1;
	j = skip_wsp(i, j, env);
	while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j]
		<= '9' && pars_colors_rgb(env, i, j, 'g') == SUCCESS)
		j++;
	j = skip_wsp(i, j, env) + 1;
	j = skip_wsp(i, j, env);
	while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j]
		<= '9' && pars_colors_rgb(env, i, j, 'b') == SUCCESS)
		j++;
	j = skip_wsp(i, j, env);
	if (env->t_map.map[i][j] == '\0')
		return (SUCCESS);
	return (ERROR_COLORS);
}

int		pars_map(t_env *env)
{
	int i;
	int j;

	i = 0;
	j = skip_wsp(i, 0, env);
	while (i < env->t_map.start_line)
	{
		j = skip_wsp(i, 0, env);
		if (env->t_map.map[i][j] == 'R'
			&& (env->error = pars_resolution(env, i, j)) != SUCCESS)
			return (env->error);
		else if ((env->t_map.map[i][j] == 'F' || env->t_map.map[i][j] == 'C')
			&& (env->error = pars_colors(env, i, j)) != SUCCESS)
			return (env->error);
		else if (ft_charset("SNWE",env->t_map.map[i][j]) == 1
			&& (env->error = pars_textures(env, i, j)) != SUCCESS)
			return (env->error);
		i++;
	}
	if ((env->error = check_textures(env)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}
