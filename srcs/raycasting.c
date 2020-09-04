#include "../includes/cub3d.h"

int quit(t_env *env)
{
    if (env->win_ptr)
        mlx_destroy_window(env->mlx_ptr, env->win_ptr);
    if (env->img)
        free(env->img);
    env->img = NULL;
    if (env->mlx_ptr)
        free(env->mlx_ptr);
    exit(1);
}

int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int key_press(int key, t_env *env)
{
    if (key == KEY_UP)
        env->mvt.up = 1;
    if (key == KEY_DOWN)
        env->mvt.dwn = 1;
    if (key == KEY_LEFT)
        env->mvt.lft = 1;
    if (key == KEY_RIGHT)
        env->mvt.rgt = 1;
    if (key == KEY_ESCAPE)
    {
        quit(env);
        
    }
    return (SUCCESS);
}

int key_release(int key, t_env *env)
{
    if (key == KEY_UP)
        env->mvt.up = 0;
    if (key == KEY_DOWN)
        env->mvt.dwn = 0;
    if (key == KEY_LEFT)
        env->mvt.lft = 0;
    if (key == KEY_RIGHT)
        env->mvt.rgt = 0;
    return (SUCCESS);
}

// void my_mlx_pixel_put(t_env *env, int x, int y, int color)
// {
//     char *dst;

//     dst = env->img->addr + (y * env->img->line_length + x * (env->img->bits_pp / 8));

//     *(unsigned int *)dst = color;

// }

void my_mlx_pixel_put_tex(t_env *env, int x, int y, int color)
{
    // char *dst;

    // dst = img->addr + (y * img->line_length + x * (img->bits_pp / 8));
env->img->addr[(y * env->t_map.res.width + x)] = color;
    // *(unsigned int *)dst = color;
    // printf ("dst = %s\n", dst);
}

void pick_color(t_env *env)
{
    
// je veux trouver la couleur du pixel qui se trouve dans la chaine env->img_tex_WE->addr[]
    // printf(env->img_tex_WE->addr[env->ray.tex.y * env->img_tex_WE->line_length + env->ray.tex.x * env->img->bits_pp / 8];

    if (env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x] && env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x] == '1')
    {
        if (env->ray.side == 0) // SOIT WEST SOIT EAST
	    {
		    if (env->ray.step.x < 0) // WEST
            {
                env->ray.color = env->img_tex_WE->addr[(TEXHEIGHT * env->ray.tex.y + env->ray.tex.x)];
                // printf ("env->ray.color = %d\n", env->ray.color);
            }
		    else                                //EAST
            {
			    env->ray.color = env->img_tex_EA->addr[(TEXHEIGHT * env->ray.tex.y + env->ray.tex.x)];
            }
	    }
	    else // NORD OU SUD
	    {
		    if (env->ray.step.y > 0) // SUD
             {
			    env->ray.color = env->img_tex_SO->addr[(TEXHEIGHT * env->ray.tex.y + env->ray.tex.x)];
             }
		    else
             {
			    env->ray.color = env->img_tex_NO->addr[(TEXHEIGHT * env->ray.tex.y + env->ray.tex.x)];
             }
	    }
        // if (env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x] && env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x] == '2')
        //     env->ray.color = env->img_tex_S->addr[(TEXHEIGHT * env->ray.tex.y + env->ray.tex.x)];
    }
}
void draw_line(t_env *env, int x, int drawstart, int drawend)
{
    int y = 0;
    while (y < drawstart)
    {
        my_mlx_pixel_put_tex(env, x, y, create_rgb(env->t_colors.rgb_C.r, env->t_colors.rgb_C.g, env->t_colors.rgb_C.b));
        y++;
    }
    while (y < drawend) //&& y < 10)
    {
        env->ray.color= 0;
        // env->ray.tex_pos = (env->ray.drawstart - env->t_map.res.height / 2 + env->ray.lineheight / 2) * env->ray.tex_step;
        env->ray.tex.y = (int)env->ray.tex_pos & (TEXHEIGHT - 1);
        env->ray.tex_pos += env->ray.tex_step;
        // printf("env->ray.tex.y = %d, env->ray.tex.x = %d\n",env->ray.tex.y, env->ray.tex.x);
        pick_color(env);
        
        my_mlx_pixel_put_tex(env, x, y, env->ray.color); //1106252);
        y++;
    }
    while (y < env->t_map.res.height)
    {
        
        my_mlx_pixel_put_tex(env, x, y, create_rgb(env->t_colors.rgb_F.r, env->t_colors.rgb_F.g, env->t_colors.rgb_F.b));
        y++;
    }
}

int go(t_env *env)
{
    if (env->img != NULL)
    {
        free(env->img); // je l'enlève car je ne fais pas de malloc pour la structure img
        env->img = NULL;
    }
    if (!(env->img = new_image(env)))
        return(IMG_FAIL);
	// // printf("ichi hey 11");
    moves(env);
    env->line = 0;
    while (env->line < env->t_map.res.width) // calc_data_raycasting
    {
        // printf("x = %d\n", env->line);
        calc_data_raycasting(env, env->line);
        draw_line(env, env->line, env->ray.drawstart, env->ray.drawend);
        env->sprites.zbuffer[env->line] = env->ray.perpwalldist;
        env->line++;
    }
    // printf("env->mlx_ptr = %p\n",env->mlx_ptr);
	// printf("env->win_ptr = %p\n",env->win_ptr);
	// printf("env->img.addr = %p\n",env->img->addr);
    draw_sprites(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img->ptr, 0, 0); // a la toute fin
    return (SUCCESS);
}



int raycasting(t_env *env) // dans init ray on a: Les vecteurs dir et plane, mlx init, l'image (avec les bpp, endian et les longueurs des lignes de pixels)
{
    if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height, "Cub3D")))
        return (MLX_FAIL);
    mlx_hook(env->win_ptr, 17, STRUCTURENOTIFYMASK, quit, env);
    mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, env);
    mlx_hook(env->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, env);
    if ((env->t_error = mlx_loop_hook(env->mlx_ptr, go, env)) != SUCCESS)
        return (env->t_error);
    mlx_loop(env->mlx_ptr);
    
    return (SUCCESS);
}