#include "includes/cub3d.h"

int main (int argc, char **argv)
{
    int i;

    i = 0;
    t_env  *env;
    env = malloc(sizeof(t_env));
    ft_make_tab(env);
    while (env->t_map.map[i])
    {
        printf("'%s'", env->t_map.map[i]);
        printf("\n");
        i++;
    }
}