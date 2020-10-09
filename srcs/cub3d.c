/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:08:37 by flolefeb          #+#    #+#             */
/*   Updated: 2020/10/09 17:52:42 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_flag_save(char *str, t_env *env)
{
	if (ft_strlen(str) != 6)
		return (WRONG_ARGS);
	if (str[0] != '-' || str[1] != '-')
		return (WRONG_ARGS);
	if (str[2] != 's' || str[3] != 'a')
		return (WRONG_ARGS);
	if (str[4] != 'v' || str[5] != 'e')
		return (WRONG_ARGS);
	env->save = 1;
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_env	*env;
	int		i;

	i = 0;
	if (!(env = malloc(sizeof(t_env))))
		return (print_error(MALLOC_FAILED, env));
	ft_bzero(env, sizeof(t_env));
	if ((argc != 2 && argc != 3))
		return (print_error(WRONG_ARGS, env));
	if ((env->error = treat_file(argv[1], env)) != SUCCESS)
		return (print_error(env->error, env));
	if ((env->error = init_raycasting(env)) != SUCCESS)
		return (print_error(env->error, env));
	if (argc == 3 && (env->error = check_flag_save(argv[2], env)) != SUCCESS)
		return (print_error(env->error, env));
	if (env->save == 1 && ((env->error = save_bmp(env)) != SUCCESS))
		return (print_error(env->error, env));
	else if ((env->error = raycasting(env)) != SUCCESS)
		return (print_error(env->error, env));
	quit(env);
	return (1);
}
