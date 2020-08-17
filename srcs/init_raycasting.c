
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
// int init_cam_plane(t_env *env)
// {

//     env->ray.pos.x = env->t_map.player_pos_x;
//     env->ray.pos.y = env->t_map.player_pos_y;

//      //which box of the map we're in
//       int mapX = env->t_map.player_pos_x;
//       int mapY = env->t_map.player_pos_y;

//     env->ray.dir.x = -1;
//     env->ray.dir.y = 0;

//     env->ray.plane.x = 0;
//     env->ray.plane.y = 0.66;

//       //length of ray from current position to next x or y-side
//       double sideDistX;
//       double sideDistY;

//       double deltaDistX;
//       double deltaDistY;

//       double perpWallDist;

//       //what direction to step in x or y-direction (either +1 or -1)
//       int stepX;
//       int stepY;

//       int hit = 0; //was there a wall hit?
//       int side; //was a NS or a EW wall hit?

//     int x;

//     x = 0;
//     while (x < env->t_map.res.width)
//     {
//       //calculate ray position and direction
//       env->ray.camera.x = 2 * x / env->t_map.res.width - 1; //x-coordinate in camera space ça commence à 0 quand x = 0, puis quand x = 1
//       env->ray.raydir.x = env->ray.dir.x + env->ray.plane.x * env->ray.camera.x;
//       env->ray.raydir.y = env->ray.dir.y + env->ray.plane.y * env->ray.camera.x;

//       //length of ray from one x or y-side to next x or y-side
//       deltaDistX = abs(1 / env->ray.dir.x);
//       deltaDistY = abs(1 / env->ray.dir.y);

//       x++;

//     }

int	    ft_new_image(t_env *env, int width, int height)
{
	// if (!(env->img = (t_img*)malloc(sizeof(t_img))))
	// 	return (MLX_FAIL);
    // env->img = (t_img*)malloc(sizeof(t_img))
	if (!(env->img.ptr = mlx_new_image(env->mlx_ptr, width, height)))
		return (MLX_FAIL);
	if (!(env->img.addr = mlx_get_data_addr(env->img.ptr, &env->img.bits_pp,
		&env->img.line_length, &env->img.endian)))
		return (MLX_FAIL);
    return(SUCCESS);
}

int init_raycasting(t_env *env) // je vais essayer sans malloc pour voir mais peut etre qu'il faut malloc
{
	env->ray.speed = 0.1;
	env->ray.map.x = env->t_map.player_pos.x;
	env->ray.map.y = env->t_map.player_pos.y;

	if (!(env->mlx_ptr = mlx_init()))
		return (MLX_FAIL);
	if (!(ft_new_image(env, env->t_map.res.width, env->t_map.res.height) != SUCCESS))
		return (MLX_FAIL);
	if (!(env->img.addr = mlx_get_data_addr(env->img.ptr, &env->img.bits_pp, &env->img.line_length,
											&env->img.endian))) // voir quand est-ce que ces données sont utilisées
		return (MLX_FAIL);
	init_dir_plane(env);
	if (!(env->ray.buff = (float *)malloc(sizeof(float) * env->t_map.res.width)))
		return (MALLOC_FAILED); // on malloc ula largeur de l'écran, tableau qui selon moi contient chaque ligne de pixel (voir si on les malloc dejà quelque part)
	return (SUCCESS);
}
