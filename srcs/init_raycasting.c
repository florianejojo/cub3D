
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
		printf("env->ray.plane.x dans init = %ff\n", env->ray.plane.x);

	}
	return (SUCCESS);
}


int init_raycasting(t_env *env) // je vais essayer sans malloc pour voir mais peut etre qu'il faut malloc
{
	env->ray.speed = 0.1;
	// env->ray.rotspeed = 0.1;
	env->ray.map.x = (int)env->t_map.player_pos.x;
	env->ray.map.y = (int)env->t_map.player_pos.y;
	if (!(env->mlx_ptr = mlx_init()))
		return (MLX_FAIL);
	if (env->img == NULL)
		env->img = new_image(env);
	// if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height, "Cub3D")))
    //     return (MLX_FAIL);
	
	init_dir_plane(env);
	// if (!(env->ray.buff = (float *)malloc(sizeof(float) * env->t_map.res.width)))
	// 	return (MALLOC_FAILED); // on malloc ula largeur de l'écran, tableau qui selon moi contient chaque ligne de pixel (voir si on les malloc dejà quelque part)
	return (SUCCESS);
}
