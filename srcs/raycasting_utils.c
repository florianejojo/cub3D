/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:06:35 by flolefeb          #+#    #+#             */
/*   Updated: 2020/09/30 17:23:11 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*new_image(t_env *env, char *file)
{
	t_img *img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->ptr = mlx_xpm_file_to_image(env->mlx_ptr, file,
		&env->tex_width, &env->tex_height)))
		return (NULL);
	if (env->tex_width != env->tex_height)
		env->tex_height = env->tex_width;
	if (!(img->addr = (unsigned int *)mlx_get_data_addr(img->ptr,
		&img->bits_pp, &img->line_length, &img->endian)))
		return (NULL);
	return (img);
}
