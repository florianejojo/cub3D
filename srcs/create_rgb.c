#include "../includes/cub3d.h"

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int		get_r(int rgb)
{
	return ((rgb >> 16 )); //& 0xFF);
}

int		get_g(int rgb)
{
	return ((rgb >> 8 ) & 0xFF);
}

int		get_b(int rgb)
{
	return (rgb & 0xFF);
}

// int main (void)
// {
//     int r = 163;
//     int g = 110;
//     int b = 173;
//     int rgb = 10710701;

//     // void *mlx_ptr;
//     // void *win_ptr;
//     // int x = 250;
//     // int y = 250;
//     // int color = 0xFFFFFF;

//     // mlx_ptr = mlx_init();
//     // win_ptr = mlx_new_window(mlx_ptr, 500, 500, "lol");
    
//     // // mlx_new_image(void *mlx_ptr, int largeur, int hauteur)
//     // while (x > 0)
//     // {
//     // mlx_pixel_put (mlx_ptr, win_ptr, x, y, color);
//     // x--; 
//     // mlx_pixel_put (mlx_ptr, win_ptr, x, y - 1, color);
//     // }
//     // x = 250;
//     // while (y > 0)
//     // {
//     // mlx_pixel_put (mlx_ptr, win_ptr, x, y, color);
//     // y--; 
//     // mlx_pixel_put (mlx_ptr, win_ptr, x, y - 1, color);
//     // }

    
//     // mlx_key_hook ( win_ptr, deal_key, (void *)0 );
//     // mlx_loop(mlx_ptr);

//     printf ("int rgb = %d\n", create_rgb(r, g, b));

//     printf ("r = %d\n", get_r(rgb));
//     printf ("g = %d\n", get_g(rgb));
//     printf ("b = %d\n", get_b(rgb));
// }

