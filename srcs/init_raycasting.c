
#include "../includes/cub3d.h"

int init_dir_plane(t_env *env) // voir si je traznsforme en void car là ca veut rien dire avec le success
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
		// printf("env->ray.plane.x dans init = %ff\n", env->ray.plane.x);

	}
	return (SUCCESS);
}


// int	init_textures(t_env *env) // on créer les img avec les données dedans 
// {
// 	env->tex_height = TEXHEIGHT;
// 	env->tex_width = TEXWIDTH;
// 	if ((env->img_tex_NO = new_image(env, TEX_)) == NULL)
// 		return (WRONG_TEX);
// 	if ((env->img_tex_SO = new_image(env, TEX_SO)) == NULL)
// 		return (WRONG_TEX);
// 	if ((env->img_tex_WE = new_image(env, TEX_WE)) == NULL)
// 		return (WRONG_TEX);
// 	if ((env->img_tex_EA = new_image(env, TEX_EA)) == NULL)
// 		return (WRONG_TEX);
// 	if ((env->sprites.img_tex_S = new_image(env, TEX_S)) == NULL)
// 		return (WRONG_TEX);
// 	return (SUCCESS);
// }

// int	init_textures(t_env *env) // on créer les img avec les données dedans 
// {
// 	if ((env->img_tex_NO = new_texture(env, env->t_textures_path.NO)) == NULL)
// 		return (WRONG_TEX);
// 	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_NO->addr);
// 	// printf ("ichi --- env->img_tex_NO->bits_pp = %d \n", env->img_tex_NO->bits_pp);
// 	// printf ("ichi --- env->img_tex_NO->line_lenght= %d \n", env->img_tex_NO->line_length);
// 	if ((env->img_tex_SO = new_texture(env, env->t_textures_path.SO)) == NULL)
// 		return (WRONG_TEX);
// 	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_SO->addr);
// 	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_SO->addr);
// 	if ((env->img_tex_WE = new_texture(env, env->t_textures_path.WE)) == NULL)
// 		return (WRONG_TEX);
// 	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_WE->addr);
// 	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_WE->addr);
// 	if ((env->img_tex_EA = new_texture(env, env->t_textures_path.EA)) == NULL)
// 		return (WRONG_TEX);
// 	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_EA->addr);
// 	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_EA->addr);
// 	if ((env->sprites.img_tex_S = new_texture(env, env->t_textures_path.S)) == NULL)
// 		return (WRONG_TEX);
// 	return (SUCCESS);
// }

int	init_textures(t_env *env) // on créer les img avec les données dedans 
{
	if ((env->img_tex_NO = new_image(env, env->t_textures_path.NO)) == NULL)
		return (WRONG_TEX);
	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_NO->addr);
	// printf ("ichi --- env->img_tex_NO->bits_pp = %d \n", env->img_tex_NO->bits_pp);
	// printf ("ichi --- env->img_tex_NO->line_lenght= %d \n", env->img_tex_NO->line_length);
	if ((env->img_tex_SO = new_image(env, env->t_textures_path.SO)) == NULL)
		return (WRONG_TEX);
	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_SO->addr);
	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_SO->addr);
	if ((env->img_tex_WE = new_image(env, env->t_textures_path.WE)) == NULL)
		return (WRONG_TEX);
	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_WE->addr);
	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_WE->addr);
	if ((env->img_tex_EA = new_image(env, env->t_textures_path.EA)) == NULL)
		return (WRONG_TEX);
	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_EA->addr);
	// printf ("ichi ------------- nv->img_tex_NO->addr = '%s'\n", env->img_tex_EA->addr);
	if ((env->img_tex_S = new_image(env, env->t_textures_path.S)) == NULL)
		return (WRONG_TEX);
	return (SUCCESS);
}

int	init_sprites(t_env *env)
{
	if (!(env->zbuffer = malloc(sizeof(double) * env->t_map.res.width)))
		return (MALLOC_FAILED);
	if (!(env->order = (int *)malloc(sizeof(int) * env->sprites.nb)))
        return (MALLOC_FAILED);
    if (!(env->distance = (double *)malloc(sizeof(double) * env->sprites.nb)))
        return (MALLOC_FAILED);
	if (!(env->pos = (t_coordf *)malloc(sizeof(t_coordf) * env->sprites.nb)))
	{
		printf ("IL Y A UN PB\n");
        return (MALLOC_FAILED);
	}
	printf("env->sprites.zbuffer = %p\n", env->zbuffer);
	printf("env->sprites.order = %p\n", env->order);
	printf("env->sprites.distance = %p\n", env->distance);
	printf("env->sprites.pos = %p\n", env->pos);

	return (SUCCESS);
	
}


int init_raycasting(t_env *env) // je vais essayer sans malloc pour voir mais peut etre qu'il faut malloc
{
	int x;
	x = 0;
	env->ray.speed = 0.1; // Je vais le mettre dans le .h et c'est le même que la vitesse de rotation, peut être que je oeux les séparer
	// env->ray.rotspeed = 0.1;
	env->ray.map.x = (int)env->t_map.player_pos.x;
	env->ray.map.y = (int)env->t_map.player_pos.y;
	if (!(env->mlx_ptr = mlx_init()))
		return (MLX_FAIL);
	if (env->img == NULL)
		env->img = new_image(env, NULL);
	// if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height, "Cub3D")))
    //     return (MLX_FAIL);
	
	if ((env->t_error = init_dir_plane(env)) != SUCCESS)
		return (env->t_error);
	if ((env->t_error = init_textures(env)) != SUCCESS)
		return (env->t_error);
	// count_sprites(env);
	if ((env->t_error = init_sprites(env)) != SUCCESS)
		return (env->t_error);
    

	// if ((env->t_error = _sprites(env)) != SUCCESS)
	// 	return (env->t_error);
	// printf("OK ICHI HEY \n");
	// if (!(*env->ray.buff = (double *)malloc(sizeof(double) * env->t_map.res.width)))
	// 	return (MALLOC_FAILED); // on malloc ula largeur de l'écran, tableau qui selon moi contient chaque ligne de pixel (voir si on les malloc dejà quelque part)
	// while (x < env->t_map.res.width)
	// {
	// 	if (!(env->ray.buff[x] = (double *)malloc(sizeof(double) * env->t_map.res.height)))
	// 		return (MALLOC_FAILED);
	// 	x++;
	// }
	return (SUCCESS);
}
