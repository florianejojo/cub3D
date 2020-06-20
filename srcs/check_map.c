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

void    find_start_end_line(t_env *env)
{
    int j;
    int i;


    j = 0;
    i = env->t_map.i;
    
    while (env->t_map.map[i] && env->t_map.start_line == 0)
    {
        
        // printf ("j avant skip = %d\n", j);
        j = skip_wsp(i, 0, env);
        // printf ("j après skip = %d\n", j);
        if (env->t_map.map[i][j])
                env->t_map.start_line = i;
        i++;
    }
    // i = ft_strlen(*env->t_map.map) - 1;
    while (env->t_map.map[i])
        i++;
    i--;
    while (env->t_map.start_line != 0 && env->t_map.end_line == 0 && env->t_map.map[i])
    {
        
        j = skip_wsp(i, 0, env);
        if (env->t_map.map[i][j])
                env->t_map.end_line = i;
        i--;
    }
    // printf ("i = %d\n", i);
    // printf ("env->t_map.start_line = %d\n", env->t_map.start_line);
    // printf ("env->t_map.end_line = %d\n", env->t_map.end_line);
    // printf ("env->t_map.map[%d] = '%s'\n", i, env->t_map.map[i]);
    
}

int     check_elems(t_env *env) // les textures je checks deja dans une autre fonction 
{
    int i;
    int j;

    i = 0;
    
    while (env->t_map.map[i] && (env->t_check.R != 1 || env->t_check.F != 1 || env->t_check.C != 1))
    {
        // printf("player pos = %d\n\n", env->t_map.player_pos);
        if (env->t_map.map[i][j])
        {
            j = skip_wsp(i, 0, env);
            if ((env->t_map.map[i][j] == 'R' && env->t_check.R != 0) || (env->t_map.map[i][j] == 'F' && env->t_check.F != 0) || (env->t_map.map[i][j] == 'C' && env->t_check.C != 0))
                return (INVALID_ELEMENTS);
            else if (env->t_map.map[i][j] == 'R')
                env->t_check.R = 1;
            else if (env->t_map.map[i][j] == 'F')
                env->t_check.F = 1;
            else if (env->t_map.map[i][j] == 'C')
                env->t_check.C = 1;
            
        }
        i++;
    }
    env->t_map.i = i;
    // printf ("env->t_check.R = %d, env->t_check.F = %d, env->t_check.F = %d\n", env->t_check.R, env->t_check.F, env->t_check.C);
    if (env->t_check.R != 1 || env->t_check.F != 1 || env->t_check.C != 1)
        return (INVALID_ELEMENTS);
    return (SUCCESS);
}


int     check_char(int i, int j, t_env *env)
{
    if (ft_charset("NSWE", env->t_map.map[i][j]) == 1)
    {
        
        if (env->t_map.player_pos == 0)
        {
            
            env->t_map.player_pos = env->t_map.map[i][j];
        }
        else
            return (TO_MANY_PLAYER_POS);
    }
    else if (ft_charset("012 ", env->t_map.map[i][j]) != 1)
        return(WRONG_CHAR);
    if (env->t_map.map[i][j] != '1')
    {
        if ((env->t_map.map[i][j] == '2' || env->t_map.map[i][j] == '0') && (find_wall_down (env, i, j) != 1 || find_wall_up(env, i, j) != 1))
            return (MAP_NOT_CLOSED);
    }
    return (SUCCESS);
}

int     check_map(t_env *env)
{
    int error;
    int i;
    int j;

    error = SUCCESS;
    
    if ((error = check_elems(env)) != SUCCESS)
    {
        return (error);
    }
    
    find_start_end_line(env);
    
    i = env->t_map.start_line;
    j = 0;
    // printf ("env->t_map.map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]); 
    j = skip_wsp(i, 0, env);
    // printf ("env->t_map.map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]); 
    while (env->t_map.map[i] && i < env->t_map.end_line)
    {
        if (line_closed(env->t_map.map[i]) != 1)
            return (LINE_NOT_CLOSED);
        while (env->t_map.map[i][j])
        {
            
            if ((error = check_char(i, j, env)) != SUCCESS)
                return (error);
            
            j++;
        }
        i++;
        j = skip_wsp(i, 0, env);
    }
    
    if (env->t_map.player_pos == 0)
    {
        
        return (NO_PLAYER_POS);
    }
    return(SUCCESS);
    
}

// int    check_map(t_env *env)
// {
//     int i;
//     int j;

//     char **map;
//     map = env->t_map.map;

//     find_start_end_lines(env, &env->t_map.start_line); // attention le start depend du t_map.i
//     find_start_end_lines(env, &env->t_map.end_line);
//     map[env->t_map.end_line + 1] = 0;
//     i = env->t_map.start_line;
//     j = 0;
//     while (map[i] && i < env->t_map.end_line)
//     {
//         if (line_closed(map[i]) != 1)
//             return (LINE_NOT_CLOSED);
//         while (map[i][j])
//         {
//             if (ft_charset("NSWE", map[i][j]) == 1)
//             {
//                 if (env->t_map.player_pos == 0)
//                     env->t_map.player_pos = map[i][j];
//                 else
//                     return (TO_MANY_PLAYER_POS);
//             }
//             else if (ft_charset("012 ", map[i][j]) != 1)
//                 return(MAP_ERROR_WRONG_CHAR);
//             if (map[i][j] != '1')
//             {
//                 if ((map[i][j] == '2' || map[i][j] == '0') && (find_wall_down (env, i, j) != 1 || find_wall_up(env, i, j) != 1))
//                     return (MAP_NOT_CLOSED);
//             }
//             j++;
//         }
//         j = 0;
//         i++;
//     }
//     if (env->t_map.player_pos == 0)
//         return (NO_PLAYER_POS);
//     return(SUCCESS);
// }