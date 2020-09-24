
#include "../includes/cub3d.h"


void    init_header_data(t_env *env)
{
	// env->bmp.fd;
	// env->bmp.padding; 
	// env->bmp.file_size;
	// env->bmp.reserved1;
	// env->bmp.reserved2;
	env->bmp.header.pixel_data_offset = 54;
	env->bmp.header.header_size = 40;
	env->bmp.header.width = env->t_map.res.width;
	env->bmp.header.height = env->t_map.res.height;
	env->bmp.header.planes = 1;
	env->bmp.header.bbp = 24;
	// env->bmp.compression;
	// env->bmp.image_size;
	// env->bmp.x_px_pm;
	// env->bmp.y_px_pm;
	// env->bmp.total_colors;
	// env->bmp.important_colors;

    // if ((env->bmp.padding = env->t_map.res.width % 4) != 0)
    //    env->bmp.padding *= 4;
    // env->bmp.header.file_size = env->bmp.header.pixel_data_offset + (env->bmp.header.bbp * env->bmp.header.height * (env->bmp.header.width + env->bmp.padding));
    env->bmp.header.file_size = env->t_map.res.width * env->t_map.res.width * 4 + 54;
}

void    write_header(t_env *env)
{
    write(env->bmp.fd, "BM", 2);
    write(env->bmp.fd, &env->bmp.header, 52);
	// write(env->bmp.fd, &env->bmp.header.file_size, 4);
	// write(env->bmp.fd,&env->bmp.header.reserved1, 2);
	// write(env->bmp.fd,&env->bmp.header.reserved2, 2);
	// write(env->bmp.fd,&env->bmp.header.pixel_data_offset, 4);
	// write(env->bmp.fd,&env->bmp.header.header_size, 4);
	// write(env->bmp.fd,&env->bmp.header.width, 4);
	// write(env->bmp.fd,&env->bmp.header.height, 4);
	// write(env->bmp.fd,&env->bmp.header.planes, 2);
	// write(env->bmp.fd,&env->bmp.header.bbp, 2);
	// write(env->bmp.fd,&env->bmp.header.compression, 4);
	// write(env->bmp.fd,&env->bmp.header.image_size, 4);
	// write(env->bmp.fd,&env->bmp.header.x_px_pm, 4);
	// write(env->bmp.fd,&env->bmp.header.y_px_pm, 4);
	// write(env->bmp.fd,&env->bmp.header.total_colors, 4);
	// write(env->bmp.fd, &env->bmp.header.important_colors, 4);
}

void    write_colors(t_env *env)
{
    int						x;
	int						y;
    unsigned int            color;

	y = env->bmp.header.height;
    x = 0;
    // ft_bzero(colors, 3);
	while (y > 0)
	{
		x = 0;
		while (x <= env->bmp.header.width)
		{
            // color = env->img->addr[(env->bmp.header.height - x) * env->bmp.header.width + y];
            color = env->img->addr[(y * env->bmp.header.width + x)];
            // printf("env->bmp.header.height - x * env->bmp.header.width + y]");
            write(env->bmp.fd, &color, 4);
            printf ("y = %d\n", y);
            printf ("x = %d\n", x);
			x++;
		}
		y--;
	}
}

int put_image_to_bmp(t_env *env)
{
    if ((env->bmp.fd = open(SAVE_FILE, O_WRONLY | O_CREAT, RIGHTS)) < 0)
		return (FILE_NOT_OPENED);
    // file_type_data(env);
    // image_info_data(env);
    init_header_data(env);
    write_header(env);
    write_colors(env);
    close(env->bmp.fd);
    return (SUCCESS);
}

int save_bmp(t_env *env)
{
    int x;
    x = 0;
    while (x < env->t_map.res.width)
    {
        calc_data_raycasting(env, x);
        draw_line(env, env->line, env->ray.drawstart, env->ray.drawend);
        env->zbuffer[env->line] = env->ray.perpwalldist;
        x++;
    }
    add_sprites(env);
    put_image_to_bmp(env);
    // quit(env);
    return (SUCCESS);
}