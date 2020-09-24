
#include "../includes/cub3d.h"

void	ft_define_ptr(t_env *env, t_header *ptr)
{
	ptr->file_size = env->t_map.res.width * env->t_map.res.height * 4 + 54;
	ptr->reserved1 = 0;
	ptr->reserved2 = 0;
	ptr->offset_bits = 54;
	ptr->size_header = 40;
	ptr->width = env->t_map.res.width;
	ptr->height = env->t_map.res.height;
	ptr->planes = 1;
	ptr->bbp = 32;
	ptr->compression = 0;
	ptr->image_size = 0;
	ptr->ppm_x = 0;
	ptr->ppm_y = 0;
	ptr->clr_total = 0;
	ptr->clr_important = 0;
}



int	ft_tab_in_img(t_env *env, int fd)
{
	int				i;
	int				x;
	int				y;
	unsigned int	*tab;

	tab = malloc(sizeof(int) * (env->t_map.res.height * env->t_map.res.width));
	// printf ("env->t_map.res.height * env->t_map.res.width = %d \n", env->t_map.res.height * env->t_map.res.width);
	if (tab == NULL)
		return (ERROR_SAVE);
	y = env->t_map.res.height - 1;
	i = 0;
	while (i < (env->t_map.res.width * env->t_map.res.height))
	{
		x = -1;
		while (++x < env->t_map.res.width)
		{
			// tab[i++] = *(unsigned int *)(env->img->addr + y * env->img->line_length + x * env->img->bits_pp / 8);

			// tab[i++] = env->img->addr[(y * env->bmp.header.width + x * env->img->bits_pp / 8)];
			tab[i++] = env->img->addr[(y * env->t_map.res.width + x)];

		}
		y--;
	}
	
	// print_tab(tab, (env->t_map.res.height * env->t_map.res.width));
	// print_tab(env->img->addr, (env->t_map.res.height * env->t_map.res.width));
	if (write(fd, tab, env->t_map.res.width * env->t_map.res.height * 4) == -1)
	{
		free(tab);
		return (ERROR_SAVE);
	}
	free(tab);
	return(SUCCESS);
}

void print_tab(unsigned int *tab, int size)
{
	int i;
	i = 0;
	while (i < size)
	{
		printf("tab[%d] = %d\n", i, tab[i]);
		i++;
	}

}

int	put_image_to_bmp(t_env *env)
{
	int			fd;
	t_header	ptr;

	ft_define_ptr(env, &ptr);
	fd = open(SAVE_FILE, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (FILE_NOT_OPENED);
	write(fd, "BM", 2);
	write(fd, &ptr, 52);
	if (ft_tab_in_img(env, fd) != SUCCESS)
		return (ERROR_SAVE);
	close(fd);
	return (SUCCESS);
}

int save_bmp(t_env *env)
{
    int x;
    x = 0;
    while (x < env->t_map.res.width)
    {
        calc_data_raycasting(env, x);
        draw_line(env, x, env->ray.drawstart, env->ray.drawend);
        env->zbuffer[x] = env->ray.perpwalldist;
        x++;
    }
    // add_sprites(env);
	print_tab(env->img->addr, (env->t_map.res.height * env->t_map.res.width));
    put_image_to_bmp(env);
    // quit(env);
    return (SUCCESS);
}