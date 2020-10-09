/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:21:28 by flolefeb          #+#    #+#             */
/*   Updated: 2020/10/09 16:48:15 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	define_ptr(t_env *env, t_header *ptr)
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

int		tab_in_img(t_env *env, int fd)
{
	int				i;
	int				x;
	int				y;
	unsigned int	*tab;

	if (!(tab = malloc(sizeof(int) *
		(env->t_map.res.height * env->t_map.res.width))))
		return (ERROR_SAVE);
	y = env->t_map.res.height - 1;
	i = 0;
	while (i < (env->t_map.res.width * env->t_map.res.height))
	{
		x = -1;
		while (++x < env->t_map.res.width)
			tab[i++] = env->img->addr[(y * env->t_map.res.width + x)];
		y--;
	}
	if (write(fd, tab, env->t_map.res.width * env->t_map.res.height * 4) == -1)
	{
		free(tab);
		return (ERROR_SAVE);
	}
	if (tab)
		free(tab);
	return (SUCCESS);
}

int		put_image_to_bmp(t_env *env)
{
	int			fd;
	t_header	ptr;

	define_ptr(env, &ptr);
	fd = open(SAVE_FILE, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (FILE_NOT_OPENED);
	write(fd, "BM", 2);
	write(fd, &ptr, 52);
	if (tab_in_img(env, fd) != SUCCESS)
		return (ERROR_SAVE);
	close(fd);
	return (SUCCESS);
}

int		save_bmp(t_env *env)
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
	put_image_to_bmp(env);
	return (SUCCESS);
}
