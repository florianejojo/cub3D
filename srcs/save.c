
#include "../includes/cub3d.h"


static void		set_in_char(char *start, int value)
{
	start[0] = (char)(value);
	start[1] = (char)(value >> 8);
	start[2] = (char)(value >> 16);
	start[3] = (char)(value >> 24);
}

void    file_type_data(t_env *env)
{
    ft_bzero(env->bmp.file_header, BM_FILE_HEADER_SIZE);
    if ((env->bmp.padding = env->t_map.res.width % 4) != 0)
       env->bmp.padding *= 4;
    env->bmp.width = env->t_map.res.width;
    env->bmp.height = env->t_map.res.height;
    env->bmp.file_header[0] = (unsigned char)'B'; // voir si on doit mettre uniqgned char
    env->bmp.file_header[1] = (unsigned char)'M';
    env->bmp.file_size = PIXEL_DATA_OFFSET + (BPP * env->bmp.height * (env->bmp.width + env->bmp.padding));
    set_in_char(env->bmp.file_header + 2, env->bmp.file_size);
	set_in_char(env->bmp.file_header + 10, PIXEL_DATA_OFFSET);

}

void    image_info_data(t_env *env)
{
    ft_bzero(env->bmp.img_header, BM_INFO_HEADER_SIZE);
    set_in_char(env->bmp.img_header, BM_INFO_HEADER_SIZE); // ca prend 4
	set_in_char(env->bmp.img_header + 4, env->bmp.width);
	set_in_char(env->bmp.img_header + 8, env->bmp.height);
	*(env->bmp.img_header + 12) = (unsigned char)(1); // ca prend 2
    set_in_char(env->bmp.img_header + 14, BPP); // ca prend 2
}

int				write_data_file(t_env *env)
{
	if ((write(env->bmp.fd, env->bmp.file_header, BM_FILE_HEADER_SIZE)) < 0)
	{
		close(env->bmp.fd);
		return (ERROR_SAVE);
	}
	if ((write(env->bmp.fd, env->bmp.img_header, BM_INFO_HEADER_SIZE)) < 0)
	{
		close(env->bmp.fd);
		return (ERROR_SAVE);
	}
	return (SUCCESS);
}
int   copy_colors(t_env *env)
{
	int						i;
	int						j;

	i = 0;
	while (i < env->bmp.height)
	{
        printf ("i = %d, env->bmp.height = %d\n", i,env->bmp.height );
		j = 0;
		while (j < env->bmp.width)
		{
            env->bmp.rgb = env->img->addr[(env->bmp.height - i) * env->bmp.width + j];
			// env->bmp.r = get_r(env->img->addr[(env->bmp.height - i) * env->bmp.width + j]);
			// env->bmp.g = get_g(env->img->addr[(env->bmp.height - i) * env->bmp.width + j]);
			// env->bmp.b = get_b(env->img->addr[(env->bmp.height - i) * env->bmp.width + j]);
            env->bmp.r = get_r(env->bmp.rgb);
			env->bmp.g = get_g(env->bmp.rgb);
			env->bmp.b = get_b(env->bmp.rgb);
            // printf ("r = %d, g = %d, b = %d\n", env->bmp.r,env->bmp.g, env->bmp.b);
            // env->bmp.rgb = create_rgb(env->bmp.r, env->bmp.g, env->bmp.b);
			if ((write(env->bmp.fd, env->bmp.b, 1)) < 0)
				return (ERROR_SAVE);
			if ((write(env->bmp.fd, env->bmp.g, 1)) < 0)
				return (ERROR_SAVE);
			if ((write(env->bmp.fd, env->bmp.r, 1)) < 0)
				return (ERROR_SAVE);
            // if ((write(env->bmp.fd, &env->bmp.rgb, 3)) < 0)
			// 	return (ERROR_SAVE);
			j++;
		}
		i++;
	}
    return (SUCCESS);
}

int put_image_to_bmp(t_env *env)
{
    if ((env->bmp.fd = open(SAVE_FILE, O_WRONLY | O_CREAT, RIGHTS)) < 0)
		return (FILE_NOT_OPENED);
    file_type_data(env);
    image_info_data(env);
    write_data_file(env);
    copy_colors(env);
    close(env->bmp.fd );
    return (SUCCESS);
}



int save(t_env *env)
{
    int x;
    x = 0;
    if (!(env->img = new_image(env, NULL)))
        return(IMG_FAIL);
    
    while (x < env->t_map.res.width)
    {
        calc_data_raycasting(env, x);
        draw_line(env, env->line, env->ray.drawstart, env->ray.drawend);
        env->zbuffer[env->line] = env->ray.perpwalldist;
        x++;

    }
    add_sprites(env);
    put_image_to_bmp(env);
    return (SUCCESS);

}


int check_flag_save(char *str, t_env *env)
{
    char *str_dup;

    if (ft_strlen(str) != 6)
        return (WRONG_ARGS);
    str_dup = ft_strdup(str);
    
    if (ft_strncmp(str, str_dup, 6) != 0)
    {
        printf("str_dup = %s\n", str_dup);
        free(str_dup);
        
        return (WRONG_ARGS);
    }
    if (str_dup)
        free(str_dup);
    env->save = 1;
    save(env);
    return (SUCCESS);
    
}
