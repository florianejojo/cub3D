#include "includes/cub3d.h"

int		check_flag_save(char *str, t_env *env)
{
	char *str_dup;
	if (ft_strlen(str) != 6)
		return (WRONG_ARGS);
	str_dup = ft_strdup(str);	
	if (ft_strncmp(str, str_dup, 6) != 0)
	{
		free(str_dup);
		return (WRONG_ARGS);
	}
	if (str_dup)
		free(str_dup);
	env->save = 1;
	return (SUCCESS); 
}

int		main (int argc, char **argv)
{
	int i;
	
	i = 0;
	t_env  *env;
	env = malloc(sizeof(t_env));
	ft_bzero(env, sizeof(t_env));
	if ((argc != 2 && argc != 3))
		return (0);
	if ((env->t_error = init_map(argv[1], env)) != SUCCESS)
		return(print_error(env->t_error));
	if ((env->t_error = init_raycasting(env)) != SUCCESS)
		return(print_error(env->t_error));
	if (argc == 3 && (env->t_error = check_flag_save(argv[2], env)) != SUCCESS) // Test si j'écris mal "save",
		return(print_error(env->t_error));
	if (env->save == 1)
	{
		if ((env->t_error = save_bmp(env)) == SUCCESS)
			return(SUCCESS);
		else 
			return (print_error(env->t_error));
		}
		else if ((env->t_error = raycasting(env)) != SUCCESS)
			return(print_error(env->t_error));
		return (1);
}