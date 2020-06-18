#include "../includes/cub3d.h"

// void make_tab(char *file, t_env *env)
// {
//     int fd;
//     int ret;
//     char buf[10];
//     char *str;
//     int i;
//     i = 0;

//     if ((fd = open(file, O_RDONLY)) < 0)
//         printf("fd = %d\n", fd);
//     while ((ret = read(fd, buf, 1)) > 0)
//         env->t_map.nb_char++;
//     str = (char *)malloc(sizeof(char) * (env->t_map.nb_char + 1));
//     close(fd);
//     fd = open(file, O_RDONLY);
//     while ((ret = read(fd, buf, 1)) > 0)
//         str[i++] = buf[0];
//     str[i] = '\0';
//     env->t_map.map = ft_split(str, '\n'); 
//     close(fd);
//     free(str); 
// }

void pars_resolution(t_env *env, int i, int j)
{
    while (env->t_map.map[i][j] == ' ')
        j++;
    while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
        env->t_res.width = env->t_res.width * 10 + env->t_map.map[i][j] - 48;
        j++;
    }
    while (env->t_map.map[i][j] == ' ')
        j++;
    while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
        env->t_res.height = env->t_res.height * 10 + env->t_map.map[i][j] - 48;
        j++;
    }
    while (env->t_map.map[i][j] == ' ')
        j++;
    // if (env->t_map.map[i][j] != '\0' || env->t_res.width <= 0 || env->t_res.height <= 0)
    //     env->t_error = ERROR_INVALID_ELEMENTS;
}



int pars_elem(t_env *env) // modif avec wsp
{
    int i;
    int j;

    i = 0;
    
    // printf("ft_charset = %d\n", ft_charset("RNSWEFC", env->t_map.map[i][0]));
    while (env->t_map.map[i] && env->t_map.map[i][j])
    {
        j = skip_wsp(i, 0, env);
        if (env->t_map.map[i][j] == 'R')
        {
            return(pars_resolution(env, i, (j + 1)));
        }
        else if (env->t_map.map[i][j] == 'F' || env->t_map.map[i][j] == 'C')
        {
            return(pars_colors(env, i, (j + 1)));
        }
        else if (ft_charset("SNWE",env->t_map.map[i][j] == 1))
        {
            return(pars_textures(env, i, (j + 2)));
        }
        i++;
    }
    env->t_map.i = i - 1; // on choppe la ligne après tous les éléments
//    printf("t_map.i = %d\n\n", env->t_map.i); 
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
