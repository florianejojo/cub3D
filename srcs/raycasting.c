#include "../includes/cub3d.h"

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
        mlx_destroy_window(env->mlx_ptr, env->win_ptr);
        if (env->img)
            free(env->img);
		env->img = NULL;
        if (env->mlx_ptr)
            free(env->mlx_ptr);
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
    if (key == KEY_ESCAPE)
    	{
        mlx_destroy_window(env->mlx_ptr, env->win_ptr);
        if (env->mlx_ptr)
            free(env->mlx_ptr);
    }
    return (SUCCESS);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_pp / 8));
    *(unsigned int *)dst = color;
}
void pick_color(t_env *env)
{
    //choose wall color
    // env->ray.RGBcolor_C = create_rgb(env->t_colors.rgb_C.r, env->t_colors.rgb_C.g, env->t_colors.rgb_C.b);
    // env->ray.RGBcolor_F = create_rgb(env->t_colors.rgb_F.r, env->t_colors.rgb_F.g, env->t_colors.rgb_F.b);
    if (env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x] && env->t_map.map[(int)env->ray.map.y][(int)env->ray.map.x] == '1')
    {
        env->ray.tex.y = (int)env->ray.tex_pos; //& (TEXHEIGHT - 1); je ne sais pas à quoi ça sert
        env->ray.tex_pos += env->ray.tex_step;
        env->ray.color = // en fontcion de la position du mur: on utilise le chemin de texture: texture[texNum][texHeight * texY + texX]; 
        env->ray.color = create_rgb(255, 0, 127);
        if (env->ray.side == 1)
        env->ray.color = env->ray.color / 2;
    }
}
void draw_line(t_env *env, int x, int drawstart, int drawend)
{
    int y = 0;
    while (y < drawstart)
    {
        my_mlx_pixel_put(env->img, x, y, create_rgb(env->t_colors.rgb_C.r, env->t_colors.rgb_C.g, env->t_colors.rgb_C.b));
        y++;
    }
    while (y < drawend)
    {
        // pick_color(env); // je n'arrive pas à savoir comment ça va choisir la couleur
        pick_color(env);
        my_mlx_pixel_put(env->img, x, y, env->ray.color); //1106252);
        y++;
    }
    while (y < env->t_map.res.height)
    {
        // pick_color(env); // je n'arrive pas à savoir comment ça va choisir la couleur
        my_mlx_pixel_put(env->img, x, y, create_rgb(env->t_colors.rgb_F.r, env->t_colors.rgb_F.g, env->t_colors.rgb_F.b));
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
        calc_data_raycasting(env, env->line);
        draw_line(env, env->line, env->ray.drawstart, env->ray.drawend);
        env->line++;
    }
    // printf("env->mlx_ptr = %p\n",env->mlx_ptr);
	// printf("env->win_ptr = %p\n",env->win_ptr);
	// printf("env->img.addr = %p\n",env->img->addr);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img->ptr, 0, 0); // a la toute fin
    return (SUCCESS);
}

int raycasting(t_env *env) // dans init ray on a: Les vecteurs dir et plane, mlx init, l'image (avec les bpp, endian et les longueurs des lignes de pixels)
{
    if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height, "Cub3D")))
        return (MLX_FAIL);
    // mlx_hook(env->win_ptr, 17, STRUCTURENOTIFYMASK, deal_exit, env);
    mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, env);
    mlx_hook(env->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, env);
    if ((env->t_error = mlx_loop_hook(env->mlx_ptr, go, env)) != SUCCESS)
        return (env->t_error);
    mlx_loop(env->mlx_ptr);
    return (SUCCESS);
}