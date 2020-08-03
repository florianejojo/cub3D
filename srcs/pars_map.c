#include "../includes/cub3d.h"

// int pars_resolution(t_env *env, int i, int j)
// {
//     while (env->t_map.map[i][j] == ' ')
//         j++;
//     while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
//     {
//         env->t_map.res.width = env->t_map.res.width * 10 + env->t_map.map[i][j] - 48;
//         j++;
//     }
//     while (env->t_map.map[i][j] == ' ')
//         j++;
//     while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
//     {
//         env->t_map.res.height = env->t_map.res.height * 10 + env->t_map.map[i][j] - 48;
//         j++;
//     }
//     while (env->t_map.map[i][j] == ' ')
//         j++;
//     return (SUCCESS);
//     // if (env->t_map.map[i][j] != '\0' || env->t_map.res.width <= 0 || env->t_map.res.height <= 0)
//     //     env->t_error = ERROR_INVALID_ELEMENTS;
// }

int pars_resolution(t_env *env, int i, int j)
{
    j = skip_wsp(i, j + 1, env); // on skpi wsp après le R
    while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
        env->t_map.res.width = env->t_map.res.width * 10 + env->t_map.map[i][j] - 48;
        j++;
    }
    j = skip_wsp(i, j, env);
    while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
        env->t_map.res.height = env->t_map.res.height * 10 + env->t_map.map[i][j] - 48;
        j++;
    }
    j = skip_wsp(i, j, env);
    // printf ("env->t_map.map[%d][%d] = '%c'\n", i, j, env->t_map.map[i][j]);
    // printf("env->res.height = %d, env->res.width = %d \n",env->t_map.res.height, env->t_map.res.width);
    if (env->t_map.res.width == 0 || env->t_map.res.height == 0)
        return (ERROR_RES);
    return (SUCCESS);
    // if (env->t_map.map[i][j] != '\0' || env->t_map.res.width <= 0 || env->t_map.res.height <= 0)
    //     env->t_error = ERROR_INVALID_ELEMENTS;
}

int pars_map(t_env *env) // modif avec wsp
{
    int i;
    int j;
    int error;

    i = 0;
    
    // printf("ft_charset = %d\n", ft_charset("RNSWEFC", env->t_map.map[i][0]));
    // j = 0;
    error = 0;
    // printf ("env->t_map.end_line = %d\n", env->t_map.end_line);
    j = skip_wsp(i, 0, env);
    // printf ("env->t_map.map[%d][%d] = '%c'\n", i, j,  env->t_map.map[i][j]);
    while (i < env->t_map.start_line) //&& ft_charset("NSWECF\0 ", (env->t_map.map[i][skip_wsp(i, 0, env)])) == 1)
    {
        j = skip_wsp(i, 0, env);
        // if (env->t_map.map[i][j] != '\0') // && ft_charset("NSWECFR", env->t_map.map[i][j]) == 0)
        // {
            
        //     return (INVALID_ELEMENTS);
        // }
        // printf("DANS PARS MAP --> env->t_map.map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]);
        if (env->t_map.map[i][j] == 'R' && (error = pars_resolution(env, i, j)) != SUCCESS)
        {
            
            return(error); 
        }
        else if ((env->t_map.map[i][j] == 'F' || env->t_map.map[i][j] == 'C') && (error = pars_colors(env, i, j)) != SUCCESS)
        {
            return(error);
        }
        else if (ft_charset("SNWE",env->t_map.map[i][j]) == 1 && (error = pars_textures(env, i, j)) != SUCCESS)
        {
            
            return(error);
        }
        
        i++;
    }
    if ((error = check_textures(env)) != SUCCESS)
    {
        // printf ("ERREUR ICI \n");
        return (error);
    }
    // env->t_map.i = i - 1; // on choppe la ligne après tous les éléments
    // printf("t_map.i = %d\n\n", env->t_map.i);
    return (SUCCESS);
}



// void pars_elem(t_env *env) // fonctionne 
// {
//     int i;
// 

//     i = 0;
//  
//     // printf("ft_charset = %d\n", ft_charset("RNSWEFC", env->t_map.map[i][0]));
//     while (ft_charset("RNSWEFC", env->t_map.map[i][0]) == 1 || env->t_map.map[i][0] == '\0') // faire une fonction empty_line? pour le cas ou la lignes contient que des espaces ?
//     {
//         // printf ("env->t_map.map[%d][0] = %c", i, env->t_map.map[i][0]);
//         if (env->t_map.map[i][0] == 'R')
//         {
//         pars_resolution(env, i, 1);
//         }
//         else if (env->t_map.map[i][0] == 'F' || env->t_map.map[i][0] == 'C')
//         {
//             pars_colors(env, i, 1);
//         }
//         else if (env->t_map.map[i][0] != '\0')
//         {
//             pars_textures(env, i, 2);
//         }
//     i++;
//     }
//     env->t_map.i = i - 1; // on choppe la ligne après tous les éléments
// //    printf("t_map.i = %d\n\n", env->t_map.i); 
 
// }
