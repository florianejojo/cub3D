/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:05:46 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/18 14:08:01 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

int skip_wsp(int i, int j, t_env *env)
{
    if (env->t_map.map[i])
    {
        while (env->t_map.map[i][j] && (env->t_map.map[i][j] == ' ' || 
            env->t_map.map[i][j] == '\t' || env->t_map.map[i][j] == '\v' || 
            env->t_map.map[i][j] == '\n' || env->t_map.map[i][j] == '\f' || env->t_map.map[i][j] == '\r'))
            j++;
    // printf ("i = %d, j = %d\n", i, j);
        return (j);
    }
    return (0);
    
}

int is_wsp(int i, int j, t_env *env)
{
    if (env->t_map.map[i][j] && (env->t_map.map[i][j] == ' ' || 
        env->t_map.map[i][j] == '\t' || env->t_map.map[i][j] == '\v' || 
        env->t_map.map[i][j] == '\n' || env->t_map.map[i][j] == '\f' || env->t_map.map[i][j] == '\r'))
        return (1);
    return (0);

}

int     find_wall_up(t_env *env, int i, int j)
{
    while (env->t_map.map[i - 1][j] && env->t_map.map[i][j] != '1')
        i--;
    if (env->t_map.map[i] && env->t_map.map[i][j] == '1')
            return (1);
    return(0);
}

int     find_wall_down(t_env *env, int i, int j)
{
    while (env->t_map.map[i] && env->t_map.map[i][j] != '1')
        i++;
    if (env->t_map.map[i] && env->t_map.map[i][j] == '1')
            return (1);
    return(0);
}

// int     line_closed(char *line)
// {
//     int j;

//     j = 0;
//     while (line[j] && line[j] == ' ')
//         j++;
//     if (line[j] != '1')
//         return (0);
//     j = ft_strlen(line) - 1;
//     while (line[j] && line[j] == ' ')
//         j--;
    
//     if (line[j] != '1')
//     {
//         printf (" different de 1 ='%c'\n", line[j]);
//         return (0);
//     }
//     return (1);
// }