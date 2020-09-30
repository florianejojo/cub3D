/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:05:30 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 12:56:00 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/cub3d.h"

int     line_closed(char *line, t_env *env)
{
    int j;

    j = skip_wsp(0, 0, env);
    if (line == '\0')
        return (SUCCESS);
    // while (line[j] && line[j] == ' ')
    //     j++;
    if (line[j] != '1')
        return (LINE_NOT_CLOSED);
	printf ("ft_strlen(line) - 1 = %d\n", (ft_strlen(line) - 1));
	printf("j 1 = %d\n", j);
	j = ft_strlen(line);
	printf("j 2 = %d\n", j);

    j = skip_wsp_revers(0, j, env);
	printf("j 3 = %d\n", j);

    // while (line[j] && line[j] == ' ')
    //     j--;
    
    if (line[j] != '1')
    {
        printf (" different de 1 ='%c'\n", line[j]);
        return (LINE_NOT_CLOSED);
    }
    return (SUCCESS);
}

int    find_start_end_line(t_env *env)
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
    while (i < env->t_map.nb_lines)
        i++;
    while (env->t_map.start_line != 0 && env->t_map.end_line == 0 && i > env->t_map.i)
    {
        if (env->t_map.map[i])
        {
        j = skip_wsp(i, 0, env);
        if (env->t_map.map[i][j])
            env->t_map.end_line = i;
        }   
        i--;
    }
    if (env->t_map.start_line == 0 || env->t_map.end_line == 0 || env->t_map.i == 0)
        return (ERROR_START_END);
    return (SUCCESS);
    
}

int     check_elems(t_env *env) 
{
    int		i;
    int		j;

    i = 0;
    while (i <= env->t_map.nb_lines && (env->t_check.R != 1 || env->t_check.F != 1
		|| env->t_check.C != 1))
    {
        if (env->t_map.map[i])
        {
            j = skip_wsp(i, 0, env);
            if ((env->t_map.map[i][j] == 'R' && env->t_check.R != 0) || (env->t_map.map[i][j] == 'F'
				&& env->t_check.F != 0) || (env->t_map.map[i][j] == 'C' && env->t_check.C != 0))
                return (INVALID_ELEMENTS);
            else if (env->t_map.map[i][j] == 'R')
                env->t_check.R = 1;
            else if (env->t_map.map[i][j] == 'F')
                env->t_check.F = 1;
            else if (env->t_map.map[i][j] == 'C')
                env->t_check.C = 1;
        }
        i++;
    }
    env->t_map.i = i;
    if (env->t_check.R != 1 || env->t_check.F != 1 || env->t_check.C != 1)
        return (INVALID_ELEMENTS);
    return (SUCCESS);
}


int     check_char(int i, int j, t_env *env)
{
    if (ft_charset("NSWE", env->t_map.map[i][j]) == 1)
    {
        if (env->t_map.player_dir == 0)
        {
            env->t_map.player_dir = env->t_map.map[i][j];
            env->t_map.player_pos.x = j + 0.5;
            env->t_map.player_pos.y = i + 0.5;
            env->t_map.map[i][j] = '0';
        }
        else
            return (TO_MANY_PLAYER_POS);
    }
    else if (ft_charset("012 ", env->t_map.map[i][j]) != 1)
        return(WRONG_CHAR);
    if (env->t_map.map[i][j] != '1')
    {
        if ((env->t_map.map[i][j] == '2' || env->t_map.map[i][j] == '0')
			&& (find_wall_down (env, i, j) != 1 || find_wall_up(env, i, j) != 1))
            return (MAP_NOT_CLOSED);
    }
    return (SUCCESS);
}

int     check_map(t_env *env)
{
    int		i;
    int		j;
	
	if ((env->error = check_elems(env)) != SUCCESS)
        return (env->error);
    if ((env->error = find_start_end_line(env)) != SUCCESS)
        return (env->error);
    i = env->t_map.start_line;
    j = 0;
    j = skip_wsp(i, 0, env);
    while (i <= env->t_map.end_line)
    {
		printf ("i = %d\n", i);
        if (env->t_map.map[i] && env->t_map.map[i][j] && line_closed(env->t_map.map[i], env) != SUCCESS)
            return (LINE_NOT_CLOSED);
        while (env->t_map.map[i] && env->t_map.map[i][j])
        {
            if ((env->error = check_char(i, j, env)) != SUCCESS)
                return (env->error);
            j++;
        }
        i++;
        j = skip_wsp(i, 0, env);
    }
    if (env->t_map.player_dir == 0)
        return (NO_PLAYER_POS);
    return(SUCCESS);
}