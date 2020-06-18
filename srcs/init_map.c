
#include "../includes/cub3d.h"

int		check_file(char *file)
{
	int len;

	len = ft_strlen(s) - 1;
	if (s[len] != 'b')
		return (INVALID_FILE);
	if (s[len - 1] != 'u')
		return (INVALID_FILE);
	if (s[len - 2] != 'c')
		return (INVALID_FILE);
	if (s[len - 3] != '.')
		return (INVALID_FILE);
	return (SUCCESS);
}

int make_map(char *file, t_env *env)
{
    int fd;
    int ret;
    char buf[10];
    char *str;
    int i;
    i = 0;

    if ((fd = open(file, O_RDONLY)) < 0)
        return(FILE_NOT_OPENED)
    while ((ret = read(fd, buf, 1)) > 0)
        env->t_map.nb_char++;
    if (str = (char *)malloc(sizeof(char) * (env->t_map.nb_char + 1)) == NULL)
        return (MALLOC_FAILED)
    close(fd);
    if (fd = open(file, O_RDONLY) < 0)
        return (FILE_NOT_OPENED)
    while ((ret = read(fd, buf, 1)) > 0)
        str[i++] = buf[0];
    str[i] = '\0';
    env->t_map.map = ft_split(str, '\n');
    close(fd);
    free(str); 
    return (SUCCESS);
}

int     init_map(char *file, t_env *env)
{
    int error;

    error = SUCCESS;
    if ((error = check_file(file)) != SUCCESS) // fait
        return (error);
    else if ((error = make_map(file, env)) != SUCCESS) // fait
        return (error);
    else if ((error = check_map(env) != SUCCESS)
        return (error);
    // else if ((error = pars_map(env)) != SUCCESS) // fait
    //     return (error);
        
    return (SUCCESS);
    
    
}