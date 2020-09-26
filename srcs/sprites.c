#include "../includes/cub3d.h"

int    init_calc_sprites(t_env *env, int i) // calculs OK
{
    // i = 0; // de quel sprite on aprle 
    // printf (" 1 \n");
    env->sprites.x = env->sprite_pos_x[env->order[i]] - env->t_map.player_pos.x;
    env->sprites.y = env->sprite_pos_y[env->order[i]] - env->t_map.player_pos.y;

    // printf("env->sprites.x = %f\n", env->sprites.x);
    // printf("env->sprites.y = %f\n", env->sprites.y);
    // printf("env->sprites.inv_det = %f\n", env->sprites.inv_det);
    // printf("env->sprites.transform.x = %f\n", env->sprites.transform.x);
    // printf("env->sprites.transform.y = %f\n", env->sprites.transform.y);
    // printf("env->sprites.screen.x = %d\n", env->sprites.screen.x);
    // printf (" 2 \n");
    // printf("env->order[%d] = %p\n", i, env->order);
    env->sprites.inv_det = 1.0 / (env->ray.plane.x * env->ray.dir.y - env->ray.dir.x * env->ray.plane.y);
    env->sprites.transform.x = env->sprites.inv_det * (env->ray.dir.y * env->sprites.x - env->ray.dir.x * env->sprites.y);
    env->sprites.transform.y = env->sprites.inv_det * (-env->ray.plane.y * env->sprites.x + env->ray.plane.x * env->sprites.y); //this is actually the depth inside the screen, that what Z is in 3D
    env->sprites.screen.x = (int)((env->t_map.res.width / 2) * (1 + env->sprites.transform.x / env->sprites.transform.y));
    // printf (" 3 \n");
    // printf("-------env->sprite_pos_x[env->order[%d]] = %f\n", i, env->sprite_pos_x[env->order[i]]);
    // printf("-------env->sprite_pos_y[env->order[%d]] = %f\n", i, env->sprite_pos_y[env->order[i]]);
    return (SUCCESS);
    
    
}

void  calc_size_screen_sprites(t_env *env)
{
    env->sprites.height = abs((int)(env->t_map.res.height / env->sprites.transform.y));
    env->sprites.drawstart.y = -env->sprites.height / 2 + env->t_map.res.height / 2;
    if (env->sprites.drawstart.y < 0)
        env->sprites.drawstart.y = 0;
    env->sprites.drawend.y = env->sprites.height / 2 + env->t_map.res.height / 2;
    if (env->sprites.drawend.y >= env->t_map.res.height)
        env->sprites.drawend.y = env->t_map.res.height - 1;

    env->sprites.width = abs((int)(env->t_map.res.height / env->sprites.transform.y));
    env->sprites.drawstart.x = -env->sprites.width / 2 + env->sprites.screen.x;
    if (env->sprites.drawstart.x < 0)
        env->sprites.drawstart.x = 0;
    env->sprites.drawend.x = env->sprites.width / 2 + env->sprites.screen.x;
    if (env->sprites.drawend.x >= env->t_map.res.width)
        env->sprites.drawend.x = env->t_map.res.width - 1;
     
    // printf("env->sprites.drawstart.y = %d\n", env->sprites.drawstart.y);
    // printf("env->sprites.drawend.y = %d\n", env->sprites.drawend.y);
    // printf("env->sprites.drawstart.x = %d\n", env->sprites.drawstart.x);
    // printf("env->sprites.drawend.x = %d\n", env->sprites.drawend.x);
    
} 

void draw_sprites(t_env *env)
{
    int stripe;
    int y;
    int d;

    stripe = env->sprites.drawstart.x;

    while (stripe < env->sprites.drawend.x)
    {
        env->sprites.tex.x = (int)(256 * (stripe - (-env->sprites.width / 2 + env->sprites.screen.x)) * TEXWIDTH / env->sprites.width) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        // printf("env->sprites.tex.x = %d\n", env->sprites.tex.x);
        if (env->sprites.transform.y > 0 && stripe > 0 && stripe < env->t_map.res.width && env->sprites.transform.y < env->zbuffer[stripe])
        {
            y = env->sprites.drawstart.y;
            while (y < env->sprites.drawend.y) //for every pixel of the current stripe
            {
                d = (y) * 256 - env->t_map.res.height * 128 + env->sprites.height * 128; //256 and 128 factors to avoid floats
                env->sprites.tex.y = ((d * TEXHEIGHT) / env->sprites.height) / 256;
                env->sprites.color = env->img_tex_S->addr[TEXWIDTH * env->sprites.tex.y + env->sprites.tex.x]; //get current color from the texture
                if ((env->sprites.color & 0x00FFFFFF) != 0)
                {
                    // buffer[y][stripe] = color; 
                    my_mlx_pixel_put(env, stripe, y, env->sprites.color); //paint pixel if it isn't black, black is the invisible color
                }
                y++;
            }
        }
        stripe++;
    }
}



void    count_sprites(t_env *env)
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
                env->sprites.nb += 1;
            }
            j++;
        }
        j = 0;
        i++;
        
    }
    // env->sprites.nb--;
    // printf("env->sprites.nb = %d\n",env->sprites.nb);
}

void    stock_sprites_pos(t_env *env)
{

    int i;
    int j;
    int nb;

    nb = 0;
    i = env->t_map.start_line;
    j = 0;
    // printf ("env->sprite.nb = %d\n", env->sprites.nb);
	// printf ("env->sprite_pos_y = %p\n", env->sprite_pos_y);
    while (i <= env->t_map.end_line)
    {
        while (env->t_map.map[i][j] && nb < env->sprites.nb)
        {
            if (env->t_map.map[i][j] == '2')
            {
                env->sprite_pos_x[nb] = j + 0.5;
                env->sprite_pos_y[nb] = i + 0.5;
                printf ("le sprite = %d, a pour x = %f et y = %f\n", nb, env->sprite_pos_x[nb], env->sprite_pos_y[nb]);
	            
                nb++;
            }
            j++;
        }
        j = 0;
        i++;
        
    }
    // env->sprites.nb--;
    // printf("env->sprites.nb = %d\n",env->sprites.nb);
    // return (SUCCESS);
}

void    make_tab_distance(t_env *env)
{
    int i;
    // int temp;
    // int j;

    i = 0;
    
    while (i < env->sprites.nb)
    {
        env->order[i] = i; //on commence a 0 donc i = 0,1,2,3,4 et pour l'ordre c'est pareil + pour es distnce c'est pareil aussi
        env->distance[i] = ((env->t_map.player_pos.x - env->sprite_pos_x[i]) * (env->t_map.player_pos.x - env->sprite_pos_x[i]) + (env->t_map.player_pos.y - env->sprite_pos_y[i]) * (env->t_map.player_pos.y - env->sprite_pos_y[i]));
        // printf ("env->order[%d] = %d\n", i, env->order[i]);
        // printf ("distance[%d] = %f\n", i, env->distance[i]);

        printf ("--- le sprite = %d, a pour x = %f et y = %f\n", i, env->sprite_pos_x[i], env->sprite_pos_y[i]);
        printf ("--- et pour distane =  %f\n", env->distance[i]);

        i++;
    }
    
}

void    print_tab_int(int *tab, int size)
{
    int i = 0;
    while (i < size)
    {
        printf("tab[%d] = %d\n", i, tab[i]);
        i++;
    }
}

void    print_tab_double(double *tab, int size)
{
    int i = 0;
    while (i < size)
    {
        printf("tab[%d] = %f\n", i, tab[i]);
        i++;
    }
}

// void    sort_tab(t_env  *env)
// {
//     int i; 
//     int j;
//     int temp;

//     i = 0; 
//     j = 0;
//     temp = 0;
//         // printf(" avant env->distance[env->order[0]] = %f\n", env->distance[0]);
//         // printf(" avant env->distance[env->order[1]] = %f\n", env->distance[1]);
//     // print_tab_int(env->order, env->sprites.nb);
//     // print_tab_double(env->distance, env->sprites.nb);
//     while (i < env->sprites.nb - 1) //&& j < env->sprites.nb) // 0 < 1
//     {
//         j = i + 1;
//         while (j < env->sprites.nb)
//         {
//             // printf ("i = %d, j = %d\n", i, j);
//             if  (((env->distance[i] < env->distance[j]) && (env->order[i] < env->order[j])) || ((env->distance[i] > env->distance[j]) && (env->order[i] > env->order[j])))
//             {
                
//                 temp = env->order[i];
//                 env->order[i] = env->order[j];
//                 env->order[j] = temp;

//                 i = 0;
//                 j = i + 1;
//             }
//             j++;
//         }
//         i++;

        
//     }

//     //  while (i < env->sprites.nb - 1) //&& j < env->sprites.nb) // 0 < 1
//     // {
//     //     j = i + 1;
//     //     if  (((env->distance[i] < env->distance[j]) && (env->order[i] < env->order[j])) || ((env->distance[i] > env->distance[j]) && (env->order[i] > env->order[j])))
//     //     {
//     //         temp = env->order[i];
//     //         env->order[i] = env->order[j];
//     //         env->order[j] = temp;
//     //         i = -1;
//     //      }
//     //     i++;
//     // }
//     printf("le sprite = 0 va etre affiché en positon = %d\n", env->order[0]);
//     printf("le sprite = 1 va etre affiché en positon = %d\n", env->order[1]);
//     printf("le sprite = 2 va etre affiché en positon = %d\n", env->order[2]);
//     printf("le sprite = 3 va etre affiché en positon = %d\n", env->order[3]);
//     printf("le sprite = 4 va etre affiché en positon = %d\n", env->order[4]);
//     print_tab_int(env->order, env->sprites.nb);
//     // i = 0;
//     // printf("env->order[%d] = %d\n", i, env->order[i]);
//         // printf(" apres env->distance[env->order[0]] = %f\n", env->distance[0]);
//         // printf(" avant env->distance[env->order[1]] = %f\n", env->distance[1]);

// }

void    sort_tab(t_env  *env)
{
	int		i;
	int		temp;
	double	temp2;

	i = 0;
	while (i < env->sprites.nb - 1)
	{
		if (env->distance[i] < env->distance[i + 1])
		{
			temp2 = env->distance[i + 1];
			env->distance[i + 1] = env->distance[i];
			env->distance[i] = temp2;
			temp = env->order[i + 1];
			env->order[i + 1] = env->order[i];
			env->order[i] = temp;
			i = 0;
		}
		else
			i++;
	}
    print_tab_int(env->order, env->sprites.nb);
    print_tab_double(env->distance, env->sprites.nb);

}

int add_sprites(t_env *env)
{
    int i;
    count_sprites(env);
    if (!(env->sprite_pos_x = (double *)malloc(sizeof(double) * env->sprites.nb)))
	{
        return (MALLOC_FAILED);
	}
	if (!(env->sprite_pos_y = (double *)malloc(sizeof(double) * env->sprites.nb)))
	{
        return (MALLOC_FAILED);
	}
    
    
    printf ("env->sprites.nb = %d\n", env->sprites.nb);
    stock_sprites_pos(env);
    make_tab_distance(env);
    sort_tab(env);
    i = 0;
    while (i < env->sprites.nb)
    {
        // calc_data_sprites(env, i);
        // printf ("i = %d\n", i);
        init_calc_sprites(env, i);
        calc_size_screen_sprites(env);
        // printf("ICHI HEY\n");
        draw_sprites(env);
        // printf("ICHI HEY2 \n");
        // printf("hello %d \n", i);
        // printf("env->sprite_pos_x[0] = %f\n", env->sprite_pos_x[0]);
        // printf("env->sprite_pos_y[0] = %f\n", env->sprite_pos_y[0]);
        // printf("env->sprite_pos_x[1] = %f\n", env->sprite_pos_x[1]);
        // printf("env->sprite_pos_y[1] = %f\n", env->sprite_pos_y[1]);
        // printf("env->order[%d] = %d\n", i, env->order[i]);
        i++;
    }
    return(SUCCESS);
}