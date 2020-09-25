
#include "../includes/cub3d.h"

void    init_calc_sprites(t_env *env, int i, t_sprites *sprites) // calculs OK
{
    // i = 0; // de quel sprite on aprle 
    // printf (" 1 \n");
    //printf("-------env->t_map.player_pos.x = %f\n", env->t_map.player_pos.x);
    //printf("-------env->t_map.player_pos.y = %f\n", env->t_map.player_pos.y);
    // printf("%d\n", i);
    sprites->x = env->sprite_pos_x[env->order[i]] - env->t_map.player_pos.x;
    sprites->y = env->sprite_pos_y[env->order[i]] - env->t_map.player_pos.y;

    // printf("env->sprites->x = %f\n", env->sprites->x);
    // printf("env->sprites->y = %f\n", env->sprites->y);
    // printf("env->sprites->inv_det = %f\n", env->sprites->inv_det);
    // printf("env->sprites->transform.x = %f\n", env->sprites->transform.x);
    // printf("env->sprites->transform.y = %f\n", env->sprites->transform.y);
    // printf("env->sprites->screen.x = %d\n", env->sprites->screen.x);
    // printf (" 2 \n");
    // printf("env->order[%d] = %p\n", i, env->order);
    sprites->inv_det = 1.0 / (env->ray.plane.x * env->ray.dir.y - env->ray.dir.x * env->ray.plane.y);
    sprites->transform.x = sprites->inv_det * (env->ray.dir.y * sprites->x - env->ray.dir.x * sprites->y);
    sprites->transform.y = sprites->inv_det * (-env->ray.plane.y * sprites->x + env->ray.plane.x * sprites->y); //this is actually the depth inside the screen, that what Z is in 3D
    sprites->screen.x = (int)((env->t_map.res.width / 2) * (1 + sprites->transform.x / sprites->transform.y));
    // printf (" 3 \n");
    // printf("-------env->sprite_pos_x[env->order[%d]] = %f\n", i, env->sprite_pos_x[env->order[i]]);
    // printf("-------env->sprite_pos_y[env->order[%d]] = %f\n", i, env->sprite_pos_y[env->order[i]]);
    
    
    
}

void  calc_size_screen_sprites(t_env *env, t_sprites *sprites)
{
    sprites->height = abs((int)(env->t_map.res.height / sprites->transform.y));
    sprites->drawstart.y = -sprites->height / 2 + env->t_map.res.height / 2;
    if (sprites->drawstart.y < 0)
        sprites->drawstart.y = 0;
    sprites->drawend.y = sprites->height / 2 + env->t_map.res.height / 2;
    if (sprites->drawend.y >= env->t_map.res.height)
        sprites->drawend.y = env->t_map.res.height - 1;

    sprites->width = abs((int)(env->t_map.res.height / sprites->transform.y));
    sprites->drawstart.x = -sprites->width / 2 + sprites->screen.x;
    if (sprites->drawstart.x < 0)
        sprites->drawstart.x = 0;
    sprites->drawend.x = sprites->width / 2 + sprites->screen.x;
    if (sprites->drawend.x >= env->t_map.res.width)
        sprites->drawend.x = env->t_map.res.width - 1;
     
    // printf("env->sprites->drawstart.y = %d\n", env->sprites->drawstart.y);
    // printf("env->sprites->drawend.y = %d\n", env->sprites->drawend.y);
    // printf("env->sprites->drawstart.x = %d\n", env->sprites->drawstart.x);
    // printf("env->sprites->drawend.x = %d\n", env->sprites->drawend.x);
    
} 

void draw_sprites(t_env *env, t_sprites *sprites)
{
    int stripe;
    int y;
    int d;

    stripe = sprites->drawstart.x;

    while (stripe < sprites->drawend.x)
    {
        sprites->tex.x = (int)(256 * (stripe - (-sprites->width / 2 + sprites->screen.x)) * TEXWIDTH / sprites->width) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        // printf("env->sprites->tex.x = %d\n", env->sprites->tex.x);
        if (sprites->transform.y > 0 && stripe > 0 && stripe < env->t_map.res.width && sprites->transform.y < env->zbuffer[stripe])
        {
            y = sprites->drawstart.y;
            while (y < sprites->drawend.y) //for every pixel of the current stripe
            {
                d = (y) * 256 - env->t_map.res.height * 128 + sprites->height * 128; //256 and 128 factors to avoid floats
                sprites->tex.y = ((d * TEXHEIGHT) / sprites->height) / 256;
                sprites->color = env->img_tex_S->addr[TEXWIDTH * sprites->tex.y + sprites->tex.x]; //get current color from the texture
                if ((sprites->color & 0x00FFFFFF) != 0)
                {
                    // buffer[y][stripe] = color; 
                    my_mlx_pixel_put(env, stripe, y, sprites->color); //paint pixel if it isn't black, black is the invisible color
                }
                y++;
            }
        }
        stripe++;
    }
}



void    count_sprites(t_env *env, t_sprites *sprites)
{
    int i;
    int j;

    // env->sprites->nb = 0;
    i = env->t_map.start_line;
    j = 0;
    while (i <= env->t_map.end_line)
    {
        while (env->t_map.map[i][j])
        {
            if (env->t_map.map[i][j] == '2')
            {
                sprites->nb += 1;
            }
            j++;
        }
        j = 0;
        i++;
        
    }
    // env->sprites->nb--;
    // printf("env->sprites->nb = %d\n",env->sprites->nb);
}

void    stock_sprites_pos(t_env *env, t_sprites *sprites)
{

    int i;
    int j;
    int nb;

    nb = 0;
    i = env->t_map.start_line;
    j = 0;
    // printf ("env->sprite.nb = %d\n", env->sprites->nb);
	// printf ("env->sprite_pos_y = %p\n", env->sprite_pos_y);
    while (i <= env->t_map.end_line)
    {
        while (env->t_map.map[i][j] && nb < sprites->nb)
        {
            if (env->t_map.map[i][j] == '2')
            {
                env->sprite_pos_x[nb] = j + 0.5;
                env->sprite_pos_y[nb] = i + 0.5;
                // printf ("env->sprite_pos_x[%d] = %f\n", nb, env->sprite_pos_x[nb]);
	            // printf ("env->sprite_pos_y[%d] = %f\n", nb, env->sprite_pos_y[nb]);
                nb++;
            }
            j++;
        }
        j = 0;
        i++;
        
    }
    // env->sprites->nb--;
    // printf("env->sprites->nb = %d\n",env->sprites->nb);
    // return (SUCCESS);
}

void    make_tab_distance(t_env *env, t_sprites *sprites)
{
    int i;
    // int temp;
    // int j;

    i = 0;
    
    while (i < sprites->nb)
    {
        env->order[i] = i; //on commence a 0 donc i = 0,1,2,3,4 et pour l'ordre c'est pareil + pour es distnce c'est pareil aussi
        env->distance[i] = ((env->t_map.player_pos.x - env->sprite_pos_x[i]) * (env->t_map.player_pos.x - env->sprite_pos_x[i]) + (env->t_map.player_pos.y - env->sprite_pos_y[i]) * (env->t_map.player_pos.y - env->sprite_pos_y[i]));
        // printf ("env->order[%d] = %d\n", i, env->order[i]);
        // printf ("distance[%d] = %f\n", i, env->distance[i]);
        i++;
    }
    
}

void    sort_tab(t_env  *env, t_sprites *sprites)
{
    int i; 
    int j;
    int temp;

    i = 0; 
    j = 0;
    temp = 0;
        // printf(" avant env->distance[env->order[0]] = %f\n", env->distance[0]);
        // printf(" avant env->distance[env->order[1]] = %f\n", env->distance[1]);

    while (i < sprites->nb - 1) //&& j < env->sprites->nb) // 0 < 1
    {
        j = i + 1;
        while (j < sprites->nb)
        {
            // printf ("i = %d, j = %d\n", i, j);
            if  (((env->distance[i] < env->distance[j]) && (env->order[i] < env->order[j])) || ((env->distance[i] > env->distance[j]) && (env->order[i] > env->order[j])))
            {
                
                temp = env->order[i];
                env->order[i] = env->order[j];
                env->order[j] = temp;
                i = -1;
                j = 0;
            }
            j++;
        }
        i++;

        
    }
    i = 0;
    // printf("env->order[%d] = %d\n", i, env->order[i]);
        // printf(" apres env->distance[env->order[0]] = %f\n", env->distance[0]);
        // printf(" avant env->distance[env->order[1]] = %f\n", env->distance[1]);

}

int add_sprites(t_env *env)
{
    int i;

    t_sprites   *sprites;
    if (!(sprites = malloc(sizeof(t_sprites))))
	{
        return (MALLOC_FAILED);
	}
    count_sprites(env, sprites);
    if (!(env->sprite_pos_x = (double *)malloc(sizeof(double) * sprites->nb)))
	{
        return (MALLOC_FAILED);
	}
	if (!(env->sprite_pos_y = (double *)malloc(sizeof(double) * sprites->nb)))
	{
        return (MALLOC_FAILED);
	}
    
    if (!(env->order = (int *)malloc(sizeof(int) * sprites->nb)))
        return (MALLOC_FAILED);
    if (!(env->distance = (double *)malloc(sizeof(double) * sprites->nb)))
        return (MALLOC_FAILED);
    
    
    // printf ("env->sprites->nb = %d\n", env->sprites->nb);
    stock_sprites_pos(env, sprites);
    make_tab_distance(env, sprites);
    sort_tab(env, sprites);
    i = 0;
    while (i < sprites->nb)
    {
        // printf("lol\n");
        // calc_data_sprites(env, i);
        // printf ("i = %d\n", i);
        init_calc_sprites(env, i, sprites);
        calc_size_screen_sprites(env, sprites);
        // printf("ICHI HEY\n");
        draw_sprites(env, sprites);
        // printf("ICHI HEY2 \n");
        // printf("hello %d \n", i);
        // printf("env->sprite_pos_x[0] = %f\n", env->sprite_pos_x[0]);
        // printf("env->sprite_pos_y[0] = %f\n", env->sprite_pos_y[0]);
        // printf("env->sprite_pos_x[1] = %f\n", env->sprite_pos_x[1]);
        // printf("env->sprite_pos_y[1] = %f\n", env->sprite_pos_y[1]);
        // printf("env->order[%d] = %d\n", i, env->order[i]);
        i++;
    }
    free(sprites);
    return(SUCCESS);
}
