
#include "../includes/cub3d.h"

void ft_pars_textures(t_env *env, int i, int j) // Tester avec toutes les lettres voir si on a le bon chemin
{
  int k;
  k = 0;
  //printf("env->t_map.map[i][0] = %c, env->t_map.map[i][1] = %c\n", env->t_map.map[i][0], env->t_map.map[i][1]);
  if (env->t_map.map[i][0] == 'S' && env->t_map.map[i][1] != 'O')
    j = 1;
  while (env->t_map.map[i][j] == ' ')
    j++;
  k = j;
  while (env->t_map.map[i][j] && env->t_map.map[i][j] != ' ')
    j++;
  if (env->t_map.map[i][0] == 'S' && env->t_map.map[i][1] != 'O' && env->t_textures_path.S == NULL) // si on est sur un sprite
    env->t_textures_path.S = ft_substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'N')
    env->t_textures_path.NO = ft_substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'S')
    env->t_textures_path.SO = ft_substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'W')
    env->t_textures_path.WE = ft_substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'E')
    env->t_textures_path.EA = ft_substr(env->t_map.map[i], k, j - k);
}

void ft_pars_colors(t_env *env, int i, int j)
{
  
  while (env->t_map.map[i][j] == ' ')
    j++;
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
      
      if (env->t_map.map[i][0] == 'F')
        env->t_colors.t_rgb_F.r = env->t_colors.t_rgb_F.r * 10 + env->t_map.map[i][j] - 48;
      else 
        env->t_colors.t_rgb_C.r = env->t_colors.t_rgb_C.r * 10 + env->t_map.map[i][j] - 48;
    j++;
    }
    j++;
printf("env->t_map.map[i][j] = %c\n", env->t_map.map[i][j]);
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
      if (env->t_map.map[i][0] == 'F')
        env->t_colors.t_rgb_F.g = env->t_colors.t_rgb_F.g * 10 + env->t_map.map[i][j] - 48;
      else 
        env->t_colors.t_rgb_C.g = env->t_colors.t_rgb_C.g * 10 + env->t_map.map[i][j] - 48;
    j++;
    }
    j++;
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
      if (env->t_map.map[i][0] == 'F')
        env->t_colors.t_rgb_F.b = env->t_colors.t_rgb_F.b * 10 + env->t_map.map[i][j] - 48;
      else 
        env->t_colors.t_rgb_C.b = env->t_colors.t_rgb_C.b * 10 + env->t_map.map[i][j] - 48;
    j++;
    }
}