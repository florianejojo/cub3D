
#include "../includes/cub3d.h"

int skip_wsp(int i, int j, t_env *env)
{
    while (env->t_map.map[i][j] && env->t_map.map[i][j] == ' ')
        j++;
    return (j);
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