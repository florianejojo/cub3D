
#include "../includes/cub3d.h"

// void sort_tab(t_env *env)
// {
//     int temp;
//     int i;

//     temp = 0;
//     i = 0;
//     while (i < env->sprites.nb - 1)
//     {
//         if (env->sprites.distance[i] > env->sprites.distance[i + 1])
//         {
//             temp = env->sprites.order[i];
//             env->sprites.order[i] = env->sprites.order[i + 1];
//             env->sprites.order[i + 1] = temp;
//             i = 0;
//         }
//         i++;
//     }
// }

// void calc_data_sprites(t_env *env, int i)
// {
//     env->sprites.x = env->sprites.tab_pos[env->sprites.order[i]].x - env->t_map.player_pos.x;
//     env->sprites.y = env->sprites.tab_pos[env->sprites.order[i]].y - env->t_map.player_pos.y;
//     env->sprites.inv_det = 1.0 / (env->ray.plane.x * env->ray.dir.y - env->ray.dir.x * env->ray.plane.y);
//     env->sprites.transform.x = env->sprites.inv_det * (env->ray.dir.y * env->sprites.x - env->ray.dir.x * env->sprites.y);
//     env->sprites.transform.y = env->sprites.inv_det * (-env->ray.plane.y * env->sprites.x + env->ray.plane.x * env->sprites.y); //this is actually the depth inside the screen, that what Z is in 3D
//     env->sprites.screen.x = (int)((env->t_map.res.width / 2) * (1 + env->sprites.transform.x / env->sprites.transform.y));

//     env->sprites.height = fabs((int)(env->t_map.res.width) / (env->sprites.transform.y));
//     env->sprites.drawstart.y = -env->sprites.height / 2 + env->t_map.res.width / 2;
//     if (env->sprites.drawstart.y < 0)
//         env->sprites.drawstart.y = 0;
//     env->sprites.drawend.y = env->sprites.height / 2 + env->t_map.res.width / 2;
//     if (env->sprites.drawend.y >= env->sprites.height)
//         env->sprites.drawend.y = env->sprites.height - 1;

//     env->sprites.width = abs((int)(env->sprites.height / (env->sprites.transform.y)));
//     env->sprites.drawstart.x = -env->sprites.width / 2 + env->sprites.screen.x;
//     if (env->sprites.drawstart.x < 0)
//         env->sprites.drawstart.x = 0;
//     env->sprites.drawend.x = env->sprites.width / 2 + env->sprites.screen.x;
//     if (env->sprites.drawend.x >= env->sprites.width)
//         env->sprites.drawend.x = env->sprites.width - 1;
//     //continuer à loops
// }

// void draw_sprite(t_env *env)
// {
//     int stripe;
//     int y;
//     int d;

//     stripe = env->sprites.drawstart.x;

//     while (stripe < env->sprites.drawend.x)
//     {
//         env->sprites.tex.x = (int)(256 * (stripe - (-env->sprites.width / 2 + env->sprites.screen.x)) * TEXWIDTH / env->sprites.width) / 256;
//         //the conditions in the if are:
//         //1) it's in front of camera plane so you don't see things behind you
//         //2) it's on the screen (left)
//         //3) it's on the screen (right)
//         //4) ZBuffer, with perpendicular distance
//         if (env->sprites.transform.y > 0 && stripe > 0 && stripe < env->t_map.res.width && env->sprites.transform.y < env->sprites.zbuffer[stripe])
//         {
//             y = env->sprites.drawstart.y;
//             while (y < env->sprites.drawend.y) //for every pixel of the current stripe
//             {
//                 d = (y)*256 - env->t_map.res.height * 128 + env->sprites.height * 128; //256 and 128 factors to avoid floats
//                 env->sprites.tex.y = ((d * TEXHEIGHT) / env->sprites.height) / 256;
//                 env->sprites.color = env->sprites.img_tex_S->addr[TEXWIDTH * env->sprites.tex.y + env->sprites.tex.x]; //get current color from the texture
//                 if ((env->sprites.color & 0x00FFFFFF) != 0)
//                 {
//                     // buffer[y][stripe] = color; 
//                     my_mlx_pixel_put_tex(env, stripe, y, env->sprites.color); //paint pixel if it isn't black, black is the invisible color
//                 }
//                 y++;
//             }
//         }
//         stripe++;
//     }
// }

// void    count_sprites(t_env *env)
// {
//     int i;
//     int j;

//     env->sprites.nb = 0;
//     i = env->t_map.start_line;
//     j = 0;
//     while (i <= env->t_map.end_line)
//     {
//         while (env->t_map.map[i][j])
//         {
//             if (env->t_map.map[i][j] == '2')
//             {
//                 env->sprites.nb += 1;
//                 p
//             }
//             j++;
//         }
//         j = 0;
//         i++;
//     }

// }

void    count_and_stock_data_sprites(t_env *env)
{
    int i;
    int j;

    env->sprites.nb = 0;
    i = env->t_map.start_line;
    j = 0;
    while (i <= env->t_map.end_line)
    {
        while (env->t_map.map[i][j])
        {
            if (env->t_map.map[i][j] == '2')
            {
                env->sprites.nb += 1;  // on commence a 1
                env->sprites.pos[env->sprites.nb - 1].x = j;
                env->sprites.pos[env->sprites.nb - 1].y = i;
                
                
            }
            j++;
        }
        j = 0;
        i++;
        
    }
    // env->sprites.nb--;
    printf("env->sprites.nb = %d\n",env->sprites.nb);
    

}

void    make_and_sort_tab(t_env *env)
{
    int i;
    int temp;
    int j;

    i = 0;
    
    while (i < env->sprites.nb)
    {
        env->sprites.order[i] = i; //on commence a 0 donc i = 0,1,2,3,4 et pour l'ordre c'est pareil + pour es distnce c'est pareil aussi
        env->sprites.distance[i] = ((env->t_map.player_pos.x - env->sprites.pos[i].x) * (env->t_map.player_pos.x - env->sprites.pos[i].x) + (env->t_map.player_pos.y - env->sprites.pos[i].y) * (env->t_map.player_pos.y - env->sprites.pos[i].y));
        // printf("env->sprites.order[%d] = %d\n", i, env->sprites.order[i]);
        // printf("env->sprites.distance[%d] = %f\n", i, env->sprites.distance[i]);
        i++;
    }
  
    temp = 0;
    i = env->sprites.nb;
    j = env->sprites.nb - 1;
    while (i != 1)
    {
        while ( j != 0)
        {
            
            if (((env->sprites.distance[i] > env->sprites.distance[j]) && (env->sprites.order[i] > env->sprites.order[j]))) || ((env->sprites.distance[i] < env->sprites.distance[j]) && (env->sprites.order[i] < env->sprites.order[j])))
            {
                temp = env->sprites.order[i];
                env->sprites.order[i] = env->sprites.order[j];
                env->sprites.order[j] = temp;
            }
            j--;
        }
        i--;
        j = i - 1;
    }
    printf ("____________________\n");
      i = 0;
    while (i < env->sprites.nb)
    {
        printf("env->sprites.order[%d] = %d\n", i, env->sprites.order[i]);
        printf("env->sprites.distance[%d] = %f\n", i, env->sprites.distance[i]);
        i++;
    }
    
    
    
    
}

int add_sprites(t_env *env)
{
    // int i;
    
    count_and_stock_data_sprites(env);
    make_and_sort_tab(env);


    // i = 0;
    // sort_tab(env);
    // while (i < env->sprites.nb)
    // {
    //     calc_data_sprites(env, i);
    //     draw_sprite(env);
    //     i++;
    // }
    return(SUCCESS);
}
