
#include "../includes/cub3d.h"

int init_dir_plane(t_env *env)
{
	if (env->t_map.player_dir == 'N')
	{
		env->ray.dir.y = -1;
		env->ray.plane.x = -0.80; // pour l'angle de vue
	}
	else if (env->t_map.player_dir == 'S')
	{
		            

		env->ray.dir.y = 1;
		env->ray.plane.x = 0.80;
	}
	else if (env->t_map.player_dir == 'E')
	{
		env->ray.dir.x = 1;
		env->ray.plane.y = -0.80;
	}
	else if (env->t_map.player_dir == 'W')
	{
		env->ray.dir.x = -1;   // et donc y = 0
		env->ray.plane.y = 0.80; // et plane x = 0
	}
	return (SUCCESS);
}


int init_raycasting(t_env *env) // je vais essayer sans malloc pour voir mais peut etre qu'il faut malloc
{
	// env->ray.speed = 0.1;
	env->ray.map.x = (int)env->t_map.player_pos.x;
	env->ray.map.y = (int)env->t_map.player_pos.y;
	// printf("env->ray.map.x = %f, env->t_map.player_pos.x = %f", env->ray.map.x, env->t_map.player_pos.x);
	if (!(env->mlx_ptr = mlx_init()))
		return (MLX_FAIL);
	// printf("ichi hey 1 \n");

	// if (!(ft_new_image(env, env->t_map.res.width, env->t_map.res.height) != SUCCESS))
	// 	return (MLX_FAIL);
	if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height,
                                        "Cub3D")))
        return (MLX_FAIL);
	if (!(env->img.ptr = mlx_new_image(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height)))
		return (MLX_FAIL);
	// printf("ichi hey 2 \n");
	if (!(env->img.addr = mlx_get_data_addr(env->img.ptr, &env->img.bits_pp, &env->img.line_length,
											&env->img.endian))) // voir quand est-ce que ces données sont utilisées
		return (MLX_FAIL);
	// printf("ichi hey 3 \n");
	init_dir_plane(env);
	// if (!(env->ray.buff = (float *)malloc(sizeof(float) * env->t_map.res.width)))
	// 	return (MALLOC_FAILED); // on malloc ula largeur de l'écran, tableau qui selon moi contient chaque ligne de pixel (voir si on les malloc dejà quelque part)
	return (SUCCESS);
}
