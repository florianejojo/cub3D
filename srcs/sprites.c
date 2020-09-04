
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

void    calc_data_sprites(t_env *env)
{
    int i;

    i = 0;
    env->sprites.x = env->sprites.tab_pos[env->sprites.order[i]].x - env->t_map.player_pos.x;
    env->sprites.y = env->sprites.tab_pos[env->sprites.order[i]].y - env->t_map.player_pos.y;
    env->sprites.inv_det = 1.0 / (env->ray.plane.x * env->ray.dir.y - env->ray.dir.x * env->ray.plane.y);
    env->sprites.transform.x = env->sprites.inv_det * (env->ray.dir.y * env->sprites.x - env->ray.dir.x * env->sprites.y);
    env->sprites.transform.y = env->sprites.inv_det * (-env->ray.plane.y * env->sprites.x + env->ray.plane.x * env->sprites.y); //this is actually the depth inside the screen, that what Z is in 3D
    env->sprites.screen.x = (int)((env->t_map.res.width / 2) * (1 + env->sprites.transform.x  / env->sprites.transform.y ));
    
    env->sprites.height = abs((int)(env->t_map.res.width) / (env->sprites.transform.y));
    env->sprites.drawstart.y = -env->sprites.height / 2 + env->t_map.res.width / 2;
    if(env->sprites.drawstart.y < 0)
        env->sprites.drawstart.y = 0;
    env->sprites.drawend.y = env->sprites.height  / 2 + env->t_map.res.width / 2;
    if(env->sprites.drawend.y >= env->sprites.height)
        env->sprites.drawend.y = env->sprites.height - 1;
    
    env->sprites.width = abs( (int) (env->sprites.height / (env->sprites.transform.y)));
    env->sprites.drawstart.x = -env->sprites.width / 2 + env->sprites.screen.x;
    if(env->sprites.drawstart.x < 0)
        env->sprites.drawstart.x = 0;
    env->sprites.drawend.x = env->sprites.width / 2 + env->sprites.screen.x;
    if(env->sprites.drawend.x >= env->sprites.width)
        env->sprites.drawend.x = env->sprites.width - 1;
    //continuer à loops
}

// void    (t_env *env)
// {

// }

void    init_sprites(t_env *env)
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
    calc_data_sprites(env);
    loop(env);

}