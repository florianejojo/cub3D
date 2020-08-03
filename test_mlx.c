#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

// // int deal_key(int key, void *param)
// // {
// //     write(1, "COUCOU", 6);
// //     return (0);
// // }

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}
typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;


int             closes(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    return (1);
}




int main (void)
{
    // void *mlx_ptr;
    // void *win_ptr;
    // void *img_ptr;
    t_data img;
    t_vars vars;
    int r = 255;
    int g = 0;
    int b = 0;
    int rgb = 10710701;
    int x = 600;
    int y = 700;
    
    // int i = 0;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, x, y, "lol");
    img.img = mlx_new_image(vars.mlx, x, y);

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (g < 255 && x > (600 * 1/3))
    {
            while (y > 0)
            {
                my_mlx_pixel_put(&img, x, y, create_rgb(r,g,b));
                y--;
            }
            y = 700;

        x--;
        
        g++;
        printf ("g = %d\n", g);
    }
 
    while (x > 0)
    {
            while (y > 0)
            {
                my_mlx_pixel_put(&img, x, y, create_rgb(r,g,b));
                y --;
            }
            y = 700;

        x--;
        // g--;

    }
   
    // while (b > 0 && x > 0)
    // {
    //         while (y > 0)
    //         {
    //             my_mlx_pixel_put(&img, x, y, create_rgb(r,g,b));
    //             y --;
    //         }
    //         y = 700;

    //     x--;
    //     b--;
    // } 
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

    mlx_key_hook(vars.win, closes, &vars);
    mlx_loop(vars.mlx);
}
//-------------------------------------------------------
// // int     main(void)
// // {
// //     void    *mlx;
// //     void    *mlx_win;

// //     mlx = mlx_init();
// //     mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// //     mlx_loop(mlx);
// // }  
//-------------------------------------------------------
// typedef struct  s_vars {
//         void    *mlx;
//         void    *win;
// }               t_vars;

// int             closes(int keycode, t_vars *vars)
// {
//     mlx_destroy_window(vars->mlx, vars->win);
//     return (1);
// }

// int             main(void)
// {
//     t_vars    vars;

//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
//     mlx_hook(vars.win, 2, 1L<<0, closes, &vars);
//     mlx_loop(vars.mlx);
// } 

