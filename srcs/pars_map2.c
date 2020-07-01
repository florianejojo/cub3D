
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

// int pars_textures(t_env *env, int i, int j) // j = S N W E
// {
//   int k;
//   k = 0;
//   //printf("env->t_map.map[i][0] = %c, env->t_map.map[i][1] = %c\n", env->t_map.map[i][0], env->t_map.map[i][1]);
//   if (env->t_map.map[i][skip_wsp(i, 0, env)] == 'S' && env->t_map.map[i][skip_wsp(i, 0, env) + 1] != 'O')
//     j = skip_wsp(i, 0, env);
//   while (env->t_map.map[i][j] == ' ')
//     j++;
//   k = j;
//   while (env->t_map.map[i][j] && env->t_map.map[i][j] != ' ')
//     j++;
//   if (env->t_map.map[i][0] == 'S' && env->t_map.map[i][1] != 'O' && env->t_textures_path.S == NULL) // si on est sur un sprite
//     env->t_textures_path.S = ft_substr(env->t_map.map[i], k, j - k);
//   else if (env->t_map.map[i][0] == 'N' && env->t_textures_path.NO == NULL)
//     env->t_textures_path.NO = ft_substr(env->t_map.map[i], k, j - k);
//   else if (env->t_map.map[i][0] == 'S' && env->t_textures_path.SO == NULL)
//     env->t_textures_path.SO = ft_substr(env->t_map.map[i], k, j - k);
//   else if (env->t_map.map[i][0] == 'W' && env->t_textures_path.WE == NULL)
//     env->t_textures_path.WE = ft_substr(env->t_map.map[i], k, j - k);
//   else if (env->t_map.map[i][0] == 'E' && env->t_textures_path.EA == NULL)
//     env->t_textures_path.EA = ft_substr(env->t_map.map[i], k, j - k);
//   else
//   {
//     // printf ("PB ICI\n");
//     env->t_error = INVALID_ELEMENTS;
//   }
// }

int pars_colors_rgb(t_env *env, int i, int j, int k)
{
  if (env->t_map.map[i][skip_wsp(i, 0, env)] == 'F')
  {
    env->t_check.F = 1;
    if (k == 'r')
      env->t_colors.rgb_F.r = env->t_colors.rgb_F.r * 10 + env->t_map.map[i][j] - 48;
    else if (k == 'g')
      env->t_colors.rgb_F.g = env->t_colors.rgb_F.g * 10 + env->t_map.map[i][j] - 48;
    else
      env->t_colors.rgb_F.b = env->t_colors.rgb_F.b * 10 + env->t_map.map[i][j] - 48;
    return (SUCCESS);
  }
  else if (env->t_map.map[i][skip_wsp(i, 0, env)] == 'C')
  {
    env->t_check.C = 1;
    if (k == 'r')
      env->t_colors.rgb_C.r = env->t_colors.rgb_C.r * 10 + env->t_map.map[i][j] - 48;
    else if (k == 'g')
      env->t_colors.rgb_C.g = env->t_colors.rgb_C.g * 10 + env->t_map.map[i][j] - 48;
    else
      env->t_colors.rgb_C.b = env->t_colors.rgb_C.b * 10 + env->t_map.map[i][j] - 48;
    return (SUCCESS);
  }
  return (ERROR_COLORS);
}

// int  pars_colors_rgb(t_env *env, int i, int j, int k)
// {
//    if (env->t_map.map[i][0] == 'F')
//    {
//      env->t_check.F = 1;
//       if (k == 'r')
//         env->t_colors.rgb_F.r = env->t_colors.rgb_F.r * 10 + env->t_map.map[i][j] - 48;
//       else if (k == 'g')
//         env->t_colors.rgb_F.g = env->t_colors.rgb_F.g * 10 + env->t_map.map[i][j] - 48;
//       else
//         env->t_colors.rgb_F.b = env->t_colors.rgb_F.b * 10 + env->t_map.map[i][j] - 48;
//    }
//    else if (env->t_map.map[i][0] == 'C')
//    {
//       env->t_check.C = 1;
//       if (k == 'r')
//         env->t_colors.rgb_C.r = env->t_colors.rgb_C.r * 10 + env->t_map.map[i][j] - 48;
//       else if (k == 'g')
//         env->t_colors.rgb_C.g = env->t_colors.rgb_C.g * 10 + env->t_map.map[i][j] - 48;
//       else
//         env->t_colors.rgb_C.b = env->t_colors.rgb_C.b * 10 + env->t_map.map[i][j] - 48;
//    }

// }

int pars_colors(t_env *env, int i, int j) // ici j est sur F ou C
{
  // printf ("à l'entrée de la fonction pars colors --> env->t_map.map[%d][%d] = '%c'\n", i, j, env->t_map.map[i][j]);
  j = skip_wsp(i, j + 1, env);
  
  // printf ("avant r ---> env->t_map.map[%d][%d] = '%c'\n", i, j, env->t_map.map[i][j]);
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9' && pars_colors_rgb(env, i, j, 'r') == SUCCESS)
    j++;
  j = skip_wsp(i, j, env) + 1;
  j = skip_wsp(i, j, env); 
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9' && pars_colors_rgb(env, i, j, 'g') == SUCCESS)
    j++;
  j = skip_wsp(i, j, env) + 1;
  j = skip_wsp(i, j, env); 
  // printf ("avant b => env->t_map.map[%d][%d] = '%c'\n", i, j, env->t_map.map[i][j]);
  while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9' && pars_colors_rgb(env, i, j, 'b') == SUCCESS)
    j++;
  j = skip_wsp(i, j, env);
  if (env->t_map.map[i][j] == '\0') // checker si c'est pas j + 1
  {
  // printf ("env->t_map.map[%d][%d] = '%c'\n", i ,j, env->t_map.map[i][j]);
    return (SUCCESS);
  }
  return (ERROR_COLORS);
}

  //    int pars_colors(t_env *env, int i, int j)
  // {
  //   while (env->t_map.map[i][j] == ' ')
  //     j++;

  //   while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
  //     {
  //       pars_colors_rgb(env, i, j, 'r');
  //       j++;
  //     }
  //     j++;
  // // printf("env->t_map.map[i][j] = %c\n", env->t_map.map[i][j]);
  //   while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
  //     {
  //       pars_colors_rgb(env, i, j, 'g');
  //       j++;
  //     }
  //     j++;
  //   while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
  //     {
  //       pars_colors_rgb(env, i, j, 'b');
  //     j++;
  //     }

  // if (env->t_colors.rgb_F.r > 255 || env->t_colors.rgb_F.g > 255 || env->t_colors.rgb_F.b > 255 || env->t_colors.rgb_C.r > 255 || env->t_colors.rgb_C.g > 255 || env->t_colors.rgb_C.b > 255)
  //   env->t_error = ERROR_INVALID_ELEMENTS;
// }