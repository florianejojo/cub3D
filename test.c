# include "mlx.h"

int main (void)
{
    void *mlx;
    void *ptr;

    mlx = mlx_init();
    ptr = mlx_new_window(mlx, 800, 600, "lol");
    mlx_loop(mlx);
}