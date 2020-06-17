#include "../includes/cub3d.h"

int     line_closed(char *line)
{
    int j;

    j = 0;
    while (line[j] && line[j] == ' ')
        j++;
    if (line[j] != '1')
        return (0);
    j = ft_strlen(line) - 1;
    while (line[j] && line[j] == ' ')
        j--;
    
    if (line[j] != '1')
    {
        printf (" different de 1 ='%c'\n", line[j]);
        return (0);
    }

        
    return (1);
}

void    find_start_end_lines(t_env *env, int *start_end)
{
    int j;

    j = 0;
    if (start_end == &env->t_map.end_line)
    {
        while (env->t_map.map[env->t_map.i + 1])
            env->t_map.i++;
    }
    while (env->t_map.map[env->t_map.i] && *start_end == 0)
    {
        j = 0;
        
        while (env->t_map.map[env->t_map.i][j] && *start_end == 0)
        {
            if (env->t_map.map[env->t_map.i][j] != ' ')
                *start_end = env->t_map.i;
            j++;
        }
        
        if (start_end == &env->t_map.start_line)
            env->t_map.i++;
        else if (start_end == &env->t_map.end_line)
            env->t_map.i--;
    }
}

int     find_wall_up(t_env *env, int i, int j)
{
    while (env->t_map.map[i - 1][j] && env->t_map.map[i][j] != '1')
        i--;
    if (env->t_map.map[i] && env->t_map.map[i][j] == '1')
            return (1);
    return(0);
}

int     find_wall_down(t_env *env, int i, int j)
{
    while (env->t_map.map[i] && env->t_map.map[i][j] != '1')
        i++;
    if (env->t_map.map[i] && env->t_map.map[i][j] == '1')
            return (1);
    return(0);
}

int    check_map(t_env *env)
{
    int i;
    int j;

    char **map;
    map = env->t_map.map;
    find_start_end_lines(env, &env->t_map.start_line);
    find_start_end_lines(env, &env->t_map.end_line);
    map[env->t_map.end_line + 1] = 0;
    i = env->t_map.start_line; 
    j = 0;
    while (map[i] && i < env->t_map.end_line)
    {
        if (line_closed(map[i]) != 1)
            return (LINE_NOT_CLOSED);
        while (map[i][j])
        {
            if (ft_charset("NSWE", map[i][j]) == 1)
            {
                if (env->t_map.player_pos == 0)
                    env->t_map.player_pos = map[i][j];
                else
                    return (TO_MANY_PLAYER_POS);
            }
            else if (ft_charset("012 ", map[i][j]) != 1)
                return(MAP_ERROR_WRONG_CHAR);
            if (map[i][j] != '1')
            {
                if ((map[i][j] == '2' || map[i][j] == '0') && (find_wall_down (env, i, j) != 1 || find_wall_up(env, i, j) != 1))
                    return (MAP_NOT_CLOSED);
            }
            j++;
        }
        j = 0;
        i++;
    }
    if (env->t_map.player_pos == 0)
        return (NO_PLAYER_POS);
    return(SUCCESS);
}