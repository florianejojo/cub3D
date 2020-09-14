#include "../includes/cub3d.h"

t_img *new_image(t_env *env) //int width, int height)
{
	t_img *img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->ptr = mlx_new_image(env->mlx_ptr, env->t_map.res.width, env->t_map.res.height)))
		return (NULL);
	if (!(img->addr = (int *)mlx_get_data_addr(img->ptr, &img->bits_pp, &img->line_length, &img->endian)))
		return (NULL);
	return (img);
}

t_tex *new_texture(t_env *env, char *file)
{
	t_tex *img_tex;

	env->tex_height = TEXHEIGHT;
	env->tex_width = TEXWIDTH;

	if (!(img_tex = (t_tex *)malloc(sizeof(t_tex))))
		return (NULL);
	if (!(img_tex->ptr = mlx_xpm_file_to_image(env->mlx_ptr, file, &env->tex_width, &env->tex_height)))
		return (NULL);
	if (!(img_tex->addr = (int *)mlx_get_data_addr(img_tex->ptr, &img_tex->bits_pp, &img_tex->line_length, &img_tex->endian)))
		return (NULL);
	return (img_tex);
}


void free_textures(t_env *env)
{
	if (env->img_tex_NO)
		free(env->img_tex_NO);
	if (env->img_tex_SO)
		free(env->img_tex_NO);
	if (env->img_tex_WE)
		free(env->img_tex_NO);
	if (env->img_tex_EA)
		free(env->img_tex_NO);
	if (env->sprites.img_tex_S)
		free(env->sprites.img_tex_S);
}

void free_all(t_env *env)
{
	free_textures(env);
	if (env->t_map.map)
		free(env->t_map.map);
	if (env->sprites.zbuffer)
		free(env->sprites.zbuffer);
	if (env->sprites.order)
		free(env->sprites.order);
	if (env->sprites.distance)
		free(env->sprites.distance);
	if (env->sprites.pos)
		free(env->sprites.pos);
	if (env)
		free(env);
	// return (SUCCESS);
}