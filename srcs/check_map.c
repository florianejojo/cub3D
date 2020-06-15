#include "../includes/cub3d.h"

//regarder si la map est bien fermée par des 1 --> Le faire après avoir stocké la map dans double tableau, (fait)
//regarder si la map contient uniquement les 4 caractères : 0, 1,2,N,S,E,W

// #pour checker la map:
// #une fonction pour trouver la position de la première ligne et la dernière ligne. OK
// une fonction check charset "0, 1,2,N,S,E,W" OK mettre une fonction charset dans la libft
// #une fonction qui regarde en fonction du char (au dessus, en dessous, a droite, a gauche), seulement si c'est pas un 1.
//  puis qui regarde avec des conditions pour si c'est la première ligne (alors c'est normal que au dessus ca existe pas) et dernière ligne(alors c'est normal que en dessous ca existe pas).


int     line_closed(char *line)
{
    int j;

    j = 0;
    while (line[j] && line[j] == ' ')
    {
        j++;
    }
    if (line[j] != '1')
    {
        return (0);
    }
    j = ft_strlen(line) - 1;
    while (line[j] && line[j] == ' ')
    {
        j--;
    }
    if (line[j] != '1')
    {
        return (0);
    }
    return (1);

}

void find_start_end_lines(t_env *env, int *start_end)
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
            {
                *start_end = env->t_map.i;
                // printf ("*start_end = %d\n", *start_end);
            }
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
    while (env->t_map.map[i - 1][j] && env->t_map.map[i][j] != '1')//(map[i - 1][j] == '2' || map[i - 1][j] == '0'))
    {
        // printf("map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]);
        // printf("map[%d - 1][%d] = %c\n", i, j, env->t_map.map[i - 1][j]);
        i--;
    }
   // i++;
// printf("FINAL UP map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]);
    if (env->t_map.map[i][j] == '1')
            return (1);
    return(0);
}

int     find_wall_down(t_env *env, int i, int j)
{
    
    while (env->t_map.map[i + 1][j] && env->t_map.map[i][j] != '1')
    {
        // printf("map[%d + 1][%d] = %c\n", i, j, env->t_map.map[i + 1][j]);
        printf("map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]);
        // printf ("coucou\n");
        i++;
    }
    //i--;
    printf(" FINAL DOWN map[%d][%d] = %c\n", i, j, env->t_map.map[i][j]);
    if (env->t_map.map[i][j] && env->t_map.map[i][j] == '1')
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
    //printf("t_map.i = %d\n\n", env->t_map.i);
    find_start_end_lines(env, &env->t_map.end_line);
    map[env->t_map.end_line + 1] = 0;
    printf("env->t_map.end_line = %d\n", env->t_map.end_line);
    
    i = env->t_map.start_line; 
    j = 0;
    while (map[i] && i < env->t_map.end_line) //&& line_closed(map[i]) == 1)
    {
        // printf("map[%d] = %s\n", i, map[i]);
        if (line_closed(map[i]) != 1)
        {
            printf("line not closed map[%d]= '%s\n", i, map[i]);
            return (LINE_NOT_CLOSED);
        }
        while (map[i][j])
        {
            printf("map[%d][%d] = %c\n", i, j, map[i][j]);
            if (ft_charset("012NSWE ", map[i][j]) != 1)
            {
                return(MAP_ERROR_WRONG_CHAR);
            }
            if (map[i][j] != '1')
            {
                // printf (" find wall down = %d\n", find_wall_down(env, i, j));
                // printf ( "find wall up = %d\n",find_wall_up(env, i, j));
                if ((map[i][j] == '2' || map[i][j] == '0') && (find_wall_down (env, i, j) != 1 ))//|| find_wall_up(env, i, j) != 1))
                {
                    return (MAP_NOT_CLOSED);
                }
                
            }
           // printf ("i = %d ,j = %d\n", i, (j));
            j++;
            
        }
        // printf("line_closed(map[i]) = %d\n", line_closed(map[i]));
        printf ("i = %d\n", (i));
        j = 0;
        i++;
    }
    // printf("env->t_map.start_line = '%s'\n", env->t_map.map[env->t_map.start_line]);
    // printf("env->t_map.end_line = '%s'\n", env->t_map.map[env->t_map.end_line]);
    // find_start_line(env);
    // find_last_line(env);
    return(1);
}