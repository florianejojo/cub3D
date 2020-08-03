
#include "../includes/cub3d.h"

int	init_dir_plane(t_env *env)
{
	if (env->t_map.player_dir == 'N')
	{
		env->ray.dir.y = -1;
		env->ray.plane.x = -0.66; // pourquoi hbrulin a mis 0,80 à chaque fois ?
	}
	else if (env->t_map.player_dir == 'S')
	{
		env->ray.dir.y = 1;
		env->ray.plane.x = 0.66;
	}
	else if (env->t_map.player_dir == 'E')
	{
		env->ray.dir.x = 1;
		env->ray.plane.y = -0.66;
	}
	else if (env->t_map.player_dir == 'W')
	{
		env->ray.dir.x = -1;
		env->ray.plane.y = 0.66;
	}
	return (SUCCESS);
}

int init_ray(t_env *env) // je vais essayer dans malloc pour voir mais peut etre qu'il faut malloc
{
if (!(env->mlx_ptr = mlx_init()))
    return (MLX_FAIL);
if (!(env->img.ptr = mlx_new_image(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height)))
    return (NULL);

if (!(env->img.addr = mlx_get_data_addr(env->img.ptr, &env->img.bits_pp, &env->img.line_length,
                                 &env->img.endian)))
    return (NULL);
init_dir_plane
}

