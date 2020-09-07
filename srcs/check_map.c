#include "../includes/cub3d.h"

int     line_closed(char *line)
{
    int j;

    j = 0;
    if (line == '\0')
        return (1);
    while (line[j] && line[j] == ' ')
        j++;
    if (line[j] != '1')
        return (0);
    j = ft_strlen(line) - 1;
    while (line[j] && line[j] == ' ')
        j--;
    
    if (line[j] != '1')
    {
        // printf (" different de 1 ='%c'\n", line[j]);
        return (0);
    }
    return (1);
}

int    find_start_end_line(t_env *env)
{
    int j;
    int i;


    j = 0;
    i = env->t_map.i;
    // printf("coucou1\n");
    while (i <= env->t_map.nb_lines && env->t_map.start_line == 0)
    {
        if (env->t_map.map[i])
        {
        // printf ("i = %d\n", i);
        // printf ("j avant skip = %d\n", j);
        j = skip_wsp(i, 0, env);
        if (env->t_map.map[i][j])
            env->t_map.start_line = i;
        // printf ("j après skip = %d\n", j);
        
        }
                
        i++;
    }
    // i = ft_strlen(*env->t_map.map) - 1;
    while (i < env->t_map.nb_lines)
        i++;
    // i--;
    while (env->t_map.start_line != 0 && env->t_map.end_line == 0 && i > env->t_map.i)
    {
        if (env->t_map.map[i])
        {
        j = skip_wsp(i, 0, env);
        if (env->t_map.map[i][j])
            env->t_map.end_line = i;
        }   
        i--;
    }
    // printf ("i = %d\n", i);
//     printf ("env->t_map.map[env->t_map.start_line] = '%s'\n", env->t_map.map[env->t_map.start_line]);
// printf ("env->t_map.map[env->t_map.end_line] = '%s'\n", env->t_map.map[env->t_map.end_line]);

    // printf ("env->t_map.map[%d] = '%s'\n", i, env->t_map.map[i]);
    if (env->t_map.start_line == 0 || env->t_map.end_line == 0 || env->t_map.i == 0)
        return (ERROR_START_END);
    return (SUCCESS);
    
}

int     check_elems(t_env *env) 
{
    int i;
    int j;

    i = 0;
    
    while (i <= env->t_map.nb_lines && (env->t_check.R != 1 || env->t_check.F != 1 || env->t_check.C != 1)) // les textures je checks deja dans une autre fonction 
    {
        if (env->t_map.map[i])
        {
            j = skip_wsp(i, 0, env);
            // printf("env->t_map.map[%d][%d] = '%c'\n", i, j, env->t_map.map[i][j]);
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
    env->t_map.i = i; // sensé etre juste apres les elements
    // printf ("env->t_map.i = %d\n", env->t_map.i);
    // printf ("env->t_check.R = %d, env->t_check.F = %d, env->t_check.F = %d\n", env->t_check.R, env->t_check.F, env->t_check.C);
    if (env->t_check.R != 1 || env->t_check.F != 1 || env->t_check.C != 1)
        return (INVALID_ELEMENTS);
    return (SUCCESS);
}


int     check_char(int i, int j, t_env *env)
{
    if (ft_charset("NSWE", env->t_map.map[i][j]) == 1)
    {
        
        if (env->t_map.player_dir == 0)
        {
            
            env->t_map.player_dir = env->t_map.map[i][j];
            env->t_map.player_pos.x = j + 0.5;
            env->t_map.player_pos.y = i + 0.5;
            env->t_map.map[i][j] = '0';

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
    if ((error = find_start_end_line(env)) != SUCCESS)
        return (error);
    // printf("coucou2\n");
    i = env->t_map.start_line;
    j = 0;
    // printf ("env->t_map.map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]); 
    j = skip_wsp(i, 0, env);
    // printf ("env->t_map.map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]); 
    while (i <= env->t_map.end_line) // env->t_map.map[i] && 
    {
        // printf ("env->t_map.map[i] = '%s'\n", env->t_map.map[i]);
        if (env->t_map.map[i] && env->t_map.map[i][j] && line_closed(env->t_map.map[i]) != 1)
        {
            // printf ("ici\n");
            return (LINE_NOT_CLOSED);
        }
        while (env->t_map.map[i] && env->t_map.map[i][j])
        {
            // printf ("j = %d\n", j);
            // printf ("i = %d\n", i);
            
            // printf ("env->t_map.map[%d][%d] = '%c'\n", i, j, env->t_map.map[i][j]);
            if ((error = check_char(i, j, env)) != SUCCESS) // peut être faire une autre fonction ailleurs avec ça, peut être pars map description puis pars map
                return (error);
            // if (env->t_map.map[i][j] == '2')
            // {
            //     env->sprites.tab_pos[env->sprites.nb].x = j + 0.5;
            //     env->sprites.tab_pos[env->sprites.nb].y = i + 0.5; 
            //     env->sprites.nb += 1;
                
            // }
            j++;
        }
        i++;
        j = skip_wsp(i, 0, env);
    }
    
    if (env->t_map.player_dir == 0)
    {
        
        return (NO_PLAYER_POS);
    }
    return(SUCCESS);
    
}