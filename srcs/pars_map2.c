/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:06:24 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 12:22:22 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

int check_textures(t_env *env)
{
  if (env->t_textures_path.NO == NULL || env->t_textures_path.SO == NULL
    || env->t_textures_path.WE == NULL || env->t_textures_path.EA == NULL || env->t_textures_path.S == NULL)
      return (INVALID_TEXTURES);
  return (SUCCESS);
}

int pars_textures(t_env *env, int i, int j) // on est sur j = N S W E --> et S = S ou SO + VOIR SI ON A PLUSIEURS SPRITES
{
  int k;
  int l;

  l = j;
  //  printf("DANS PARS textures--> env->t_map.map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]);
  if (env->t_map.map[i][j] == 'S' && env->t_map.map[i][j + 1] != 'O') //  j = 3 on est sur 
  // {
    // printf ("coucou\n");
    j = skip_wsp(i, j + 1, env); // on a le début de la chaine textures
  // }
  else 
    j = skip_wsp(i, j + 2, env); 
  k = j; // k devient le début de la chaine texture 
  while (env->t_map.map[i][j] && is_wsp(i, j, env) == 0)
    j++;
  if (env->t_map.map[i][l] == 'S' && env->t_map.map[i][l + 1] == 'O' && env->t_textures_path.SO == NULL) // si on est sur un sprite
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
  j = skip_wsp(i, j, env);
  if (env->t_map.map[i][j] == '\0') // checker si c'est pas j + 1
  {
  // printf ("env->t_map.map[%d][%d] = '%c'\n", i ,j, env->t_map.map[i][j]);

    return (SUCCESS);
  }
  return (INVALID_ELEMENTS);
}


