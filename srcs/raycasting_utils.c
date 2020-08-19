#include "../includes/cub3d.h"

// int	    ft_new_image(t_env *env, int width, int height)
// {
// 	if (!(env->img = (t_img*)malloc(sizeof(t_img))))
// 	 	return (MLX_FAIL);
// 	if (!(env->img.ptr = mlx_new_image(env->mlx_ptr, width, height)))
// 		return (MLX_FAIL);
// 	printf("ichi hey 11");
// 	if (!(env->img.addr = mlx_get_data_addr(env->img.ptr, &env->img.bits_pp,
// 		&env->img.line_length, &env->img.endian)))
// 		return (MLX_FAIL);
//     return(SUCCESS);
// }