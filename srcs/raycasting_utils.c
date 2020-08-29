#include "../includes/cub3d.h"

t_img	    *new_image(t_env *env) //int width, int height)
{
    t_img *img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
	 	return (NULL);
	if (!(img->ptr = mlx_new_image(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height)))
		return (NULL);
	if (!(img->addr = mlx_get_data_addr(img->ptr, &img->bits_pp, &img->line_length, &img->endian)))
		return (NULL);
    return(img);
}

// t_img	*ft_new_image(t_env *env, int width, int height)
// {
	

// 	if (!(img = malloc(sizeof(t_img))))
// 		return (NULL);
// 	if (!(img->img_ptr = mlx_new_image(env->mlx_ptr, width, height)))
// 		return (NULL);
// 	// printf("width = %d, height = %d", width, height);
// 	if (!(img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
// 		&img->size_line, &img->endian)))
// 		return (NULL);
// 	printf("img->img_data = %p\n",img->img_data );
// 	// printf("width = %d, height = %d", width, height);
// 	img->width = width;
// 	img->height = height;
	
// 	return (img);
// }