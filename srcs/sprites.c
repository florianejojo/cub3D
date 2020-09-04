
#include "../includes/cub3d.h"

int    *sort_tab(t_env *env)
{
    int    temp;
    int    i;

    temp = 0;
    i = 0;
    while (i < env->sprites.nb - 1)
    {
        if (env->sprites.distance[i] > env->sprites.distance[i + 1])
        {
            temp = env->sprites.order[i];
            env->sprites.order[i] = env->sprites.order[i + 1];
            env->sprites.order[i + 1] = temp;
            i = 0;
        }
        i++;
    }
}

//function used to sort the sprites
void sort_sprites(t_env *env, int* order, double* dist, int nb_sprites) // les plus loin seront dessinés en premier
{
     
    
}

//  calculates the size it should have on screen,
// draws it stripe by stripe



void    draw_sprites(t_env *env)
{
    if (!(env->sprites.order = (int*)malloc(sizeof(int) * env->sprites.nb)))
        return (MALLOC_FAILED);
    if (!(env->sprites.distance = (double*)malloc(sizeof(double) * env->sprites.nb)))
        return(MALLOC_FAILED);
    int i;

    i = 0;
    while (i < env->sprites.nb)
    {
        env->sprites.order[i] = i;
        env->sprites.distance[i] = ((env->t_map.player_pos.x - env->sprites.tab_pos[i].x) * (env->t_map.player_pos.x - env->sprites.tab_pos[i].x) + (env->t_map.player_pos.y - env->sprites.tab_pos[i].y) * (env->t_map.player_pos.y - env->sprites.tab_pos[i].y));
        i++;
    }
    sort_tab(env);

}
