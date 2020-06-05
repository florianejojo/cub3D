
#include "../includes/cub3d.h"

void pars_textures(t_env *env, int i, int j) // Tester avec toutes les lettres voir si on a le bon chemin
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
    env->t_textures_path.S = substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'N'&& env->t_textures_path.NO == NULL)
    env->t_textures_path.NO = substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'S' && env->t_textures_path.SO == NULL)
    env->t_textures_path.SO = substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'W' && env->t_textures_path.WE == NULL)
    env->t_textures_path.WE = substr(env->t_map.map[i], k, j - k);
  else if (env->t_map.map[i][0] == 'E' && env->t_textures_path.EA == NULL)
    env->t_textures_path.EA = substr(env->t_map.map[i], k, j - k);
  else 
    env->t_error = ERROR_INVALID_ELEMENTS; 
  if (env->t_textures_path.S == NULL || env->t_textures_path.NO == NULL || env->t_textures_path.SO == NULL || env->t_textures_path.WE == NULL || env->t_textures_path.EA == NULL)
    env->t_error = ERROR_INVALID_ELEMENTS;
}

void  pars_colors_rgb(t_env *env, int i, int j, int k)
{
   if (env->t_map.map[i][0] == 'F')
   {
     env->t_check.F = 1;
      if (k == 'r')
        env->t_colors.t_rgb_F.r = env->t_colors.t_rgb_F.r * 10 + env->t_map.map[i][j] - 48;
      else if (k == 'g')
        env->t_colors.t_rgb_F.g = env->t_colors.t_rgb_F.g * 10 + env->t_map.map[i][j] - 48;
      else
        env->t_colors.t_rgb_F.b = env->t_colors.t_rgb_F.b * 10 + env->t_map.map[i][j] - 48;
   }
   else if (env->t_map.map[i][0] == 'C')
   {
      env->t_check.C = 1;
      if (k == 'r')
        env->t_colors.t_rgb_C.r = env->t_colors.t_rgb_C.r * 10 + env->t_map.map[i][j] - 48;
      else if (k == 'g')
        env->t_colors.t_rgb_C.g = env->t_colors.t_rgb_C.g * 10 + env->t_map.map[i][j] - 48;
      else
        env->t_colors.t_rgb_C.b = env->t_colors.t_rgb_C.b * 10 + env->t_map.map[i][j] - 48;
   }

}

void pars_colors(t_env *env, int i, int j)
{
  while (env->t_map.map[i][j] == ' ')
    j++;
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
      pars_colors_rgb(env, i, j, 'r');
      j++;
    }
    j++;
// printf("env->t_map.map[i][j] = %c\n", env->t_map.map[i][j]);
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
      pars_colors_rgb(env, i, j, 'g');
      j++;
    }
    j++;
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
      pars_colors_rgb(env, i, j, 'b');
    j++;
    }
  if (env->t_colors.t_rgb_F.r > 255 || env->t_colors.t_rgb_F.g > 255 || env->t_colors.t_rgb_F.b > 255 || env->t_colors.t_rgb_C.r > 255 || env->t_colors.t_rgb_C.g > 255 || env->t_colors.t_rgb_C.b > 255)
    env->t_error = ERROR_INVALID_ELEMENTS; 
}