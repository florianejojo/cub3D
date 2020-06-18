
#include "../includes/cub3d.h"

int skip_wsp(int i, int j, t_env *env)
{
    while (env->t_map.map[i][j] && env->t_map.map[i][j] == ' ')
        j++;
    return (j);
}
