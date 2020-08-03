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

int     closes(int keycode, t_env *env)
{
    mlx_destroy_window(env->mlx_ptr, env->win_ptr);
    return (1);
}

int ray(t_env *env)
{
    int color;
    int r;
    int g;
    int b;
    int x;
    int y;

    r = env->t_colors.rgb_C.r;
    g = env->t_colors.rgb_C.g;
    b = env->t_colors.rgb_C.b;

    x = 0;
    y = 0;

    color = create_rgb(r, g, b);
    if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height,
                                        "Cub3D")))
        return (MLX_FAIL);

    while ((g < 255) && (x < env->t_map.res.width))
    {
        while (y < env->t_map.res.height)
        {
            my_mlx_pixel_put(env, x, y, color);
            y++;
        }
        y = 0;

        x++;
        g++;
        printf("g = %d\n", g);
    }
    while (x < env->t_map.res.width && g > 0)
    {
        while (y < env->t_map.res.height)
        {
            my_mlx_pixel_put(env, x, y, create_rgb(r, g, b));
            y++;
        }
        y = 0;

        x++;
        g--;
    }
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.ptr, 0, 0);
    mlx_key_hook(env->win_ptr, closes, env);
    mlx_loop(env->mlx_ptr);
    return (SUCCESS);
}