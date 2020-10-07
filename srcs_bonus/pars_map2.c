/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:06:24 by flolefeb          #+#    #+#             */
/*   Updated: 2020/10/01 12:25:30 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		set_res_max(t_env *env)
{
	env->res_max.height = 4000;
	env->res_max.width = 4000;
}

int		check_textures(t_env *env)
{
	if (env->t_textures_path.NO == NULL || env->t_textures_path.SO == NULL
		|| env->t_textures_path.WE == NULL || env->t_textures_path.EA == NULL
		|| env->t_textures_path.S == NULL)
		return (WRONG_TEX);
	return (SUCCESS);
}

int		pars_textures_2(int i, int j, int k, t_env *env)
{
	int l;

	l = env->l;
	if (env->t_map.map[i][l] == 'S' && env->t_map.map[i][l + 1] == 'O'
		&& env->t_textures_path.SO == NULL)
		env->t_textures_path.SO = ft_substr(env->t_map.map[i], k, j - k);
	else if (env->t_map.map[i][l] == 'N' && env->t_textures_path.NO == NULL)
		env->t_textures_path.NO = ft_substr(env->t_map.map[i], k, j - k);
	else if (env->t_map.map[i][l] == 'S' && env->t_textures_path.S == NULL)
		env->t_textures_path.S = ft_substr(env->t_map.map[i], k, j - k);
	else if (env->t_map.map[i][l] == 'W' && env->t_textures_path.WE == NULL)
		env->t_textures_path.WE = ft_substr(env->t_map.map[i], k, j - k);
	else if (env->t_map.map[i][l] == 'E' && env->t_textures_path.EA == NULL)
		env->t_textures_path.EA = ft_substr(env->t_map.map[i], k, j - k);
	else
		return (INVALID_ELEMENTS);
	return (SUCCESS);
}

int		pars_textures(t_env *env, int i, int j)
{
	int		k;

	env->l = j;
	if (env->t_map.map[i][j] == 'S' && env->t_map.map[i][j + 1] != 'O')
		j = skip_wsp(i, j + 1, env);
	else
		j = skip_wsp(i, j + 2, env);
	k = j;
	while (env->t_map.map[i][j] && is_wsp(i, j, env) == 0)
		j++;
	pars_textures_2(i, j, k, env);
	j = skip_wsp(i, j, env);
	if (env->t_map.map[i][j] == '\0')
		return (SUCCESS);
	return (INVALID_ELEMENTS);
}
