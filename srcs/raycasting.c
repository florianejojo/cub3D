#include "../includes/cub3d.h"

int     create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void    my_mlx_pixel_put(t_env *env, int width, int height, int color)
{
    char *dst;

    dst = env->img.addr + (height * env->img.line_length + width * (env->img.bits_pp / 8));
    *(unsigned int *)dst = color;
}

// int     closes(int keycode, t_env *env)
// {
//     mlx_destroy_window(env->mlx_ptr, env->win_ptr);
//     return (1);
// }

int		key_press(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_W)
		env->mvt.up = 1;
	if (key == KEY_DOWN || key == KEY_S)
		env->mvt.dwn = 1;
	if (key == KEY_LEFT)
		env->mvt.lft = 1;
	if (key == KEY_RIGHT)
		env->mvt.rgt = 1;
	// if (key == KEY_ESCAPE)
	// 	deal_exit(env);
	return (SUCCESS);
}

int		key_release(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_W)
		env->mvt.up = 0;
	if (key == KEY_DOWN || key == KEY_S)
		env->mvt.dwn = 0;
	if (key == KEY_LEFT)
		env->mvt.lft = 0;
	if (key == KEY_RIGHT)
		env->mvt.rgt = 0;
	// if (key == KEY_ESCAPE)
	// 	deal_exit(env);
	return (SUCCESS);
}

void    init_vectors(t_env *env, int x) // calcul de raydir avec les 2 vacteurs: plane et dir + camera
{
    
      env->ray.camera.x = 2 * x / env->t_map.res.width - 1; //numéro de ligne verticale de pixels ou on est
      env->ray.raydir.x = env->ray.dir.x + env->ray.plane.x * env->ray.camera.x;
      env->ray.raydir.y = env->ray.dir.y + env->ray.plane.y * env->ray.camera.x;
    // env->ray.map.x = (int)env->rc.rpos.x; // c'est fait dans init ray, j'ai stocké la variable position joueur x et y dans env->ray.pos.x et y
	// env->rc.rmap.y = (int)env->rc.rpos.y;
      env->ray.deltadist.x = fabsf(1 / env->ray.raydir.x);
      env->ray.deltadist.y = fabsf(1 / env->ray.raydir.y);

    
}

void    calc_step(t_env *env)
{
    if (env->ray.raydir.x < 0)
    {
        env->ray.step.x = -1;
        env->ray.sidedist.x = (env->t_map.player_pos.x - env->ray.map.x) * env->ray.deltadist.x;
    }
    else
    {
        env->ray.step.x = 1;
        env->ray.sidedist.x = (env->ray.map.x + 1.0 - env->t_map.player_pos.x) * env->ray.deltadist.x;
    }
    if (env->ray.raydir.x < 0)
    {
        env->ray.step.y = -1;
        env->ray.sidedist.y = (env->t_map.player_pos.y - env->ray.map.y) * env->ray.deltadist.y;
    }
    else
    {
        env->ray.step.x = 1;
        env->ray.sidedist.y = (env->ray.map.y + 1.0 - env->t_map.player_pos.y) * env->ray.deltadist.y;
    }
}

perform_DDA(t_env *env)
{
    while (env->ray.hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (env->ray.sidedist.x < env->ray.sidedist.y)
        {
          env->ray.sidedist.x += env->ray.deltadist.x;
            env->ray.map.x += env->ray.step.x;
            env->ray.side = 0;
        }
        else
        {
          env->ray.sidedist.y += env->ray.deltadist.y;
            env->ray.map.y += env->ray.step.y;
            env->ray.side = 1;
        }
        //Check if ray has hit a wall
        if (env->t_map.map[(int)env->ray.map.x][(int)env->ray.map.y] != '0')
            env->ray.hit = 1;
      } 
}

calc_perpwalldist(t_env *env)
{
    //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (env->ray.side == 0)
        env->ray.perpwalldist = (env->ray.map.x - env->t_map.player_pos.x + (1 - env->ray.step.x) / 2) / env->ray.dir.x;
    else           
        env->ray.perpwalldist = (env->ray.map.y - env->t_map.player_pos.y + (1 - env->ray.step.y) / 2) / env->ray.dir.y;
}

void display_screen(t_env *env)
{
    int x;

    x = 0;
    while (x < env->t_map.res.width)
    {
    init_vectors(env, x); // ici on a, le numéro de ligne verticale de pixels ou on est, on a déjà initilaité plane et dir avant, maintenant on calcule raydir
    calc_step(env);
    perform_DDA(env);
    calc_perpwalldist(env);
    x++; 
    }
    
}

int     go(t_env *env)
{
    // ft_free_img(env); // je l'enlève car je ne fais pas de malloc pour la structure img
	if (!(ft_new_image(env, env->t_map.res.width, env->t_map.res.height) != SUCCESS))
    return (MLX_FAIL);
    // moves(env);
    display_screen(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.ptr, 0, 0); // a la toute fin
    // mlx_key_hook(env->win_ptr, closes, env);

    return (SUCCESS);
}

int ray(t_env *env) // dans init ray on a: Les vecteurs dir et plane, mlx init, l'image (avec les bpp, endian et les longueurs des lignes de pixels)
{
    // int color; // a créer dans la structure
    // int r;
    // int g;
    // int b;
    // unsigned int x;
    // unsigned int y;

    // r = env->t_colors.rgb_C.r;
    // g = env->t_colors.rgb_C.g;
    // b = env->t_colors.rgb_C.b;

    // x = 0;
    // y = 0;

    // color = create_rgb(r, g, b);
    if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height,
                                        "Cub3D")))
        return (MLX_FAIL);
    mlx_hook(env->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, env);
    mlx_hook(env->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, env);
    if ((env->t_error = mlx_loop_hook(env->win_ptr, go, env)) != SUCCESS)
        return (env->t_error);
    mlx_loop(env->mlx_ptr);
    return (SUCCESS);
}