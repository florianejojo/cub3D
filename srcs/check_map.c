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
        return (LINE_NOT_CLOSED);
    }
    j = ft_strlen(line) - 1;
    while (line[j] && line[j] == ' ')
    {
        j--;
    }
    if (line[j] != '1')
    {
        return (LINE_NOT_CLOSED);
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
    // printf("t_map.i = %d\n\n", env->t_map.i);
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

int     find_wall_up(char **map, int i, int j)
{
    while (map[i][j])
    {
        if (map[i][j] == '1')
            return (1);
        i--;
    }
    return(MAP_NOT_CLOSED);
}

int     find_wall_down(char **map, int i, int j)
{
    while (map[i][j])
    {
        if (map[i][j] == '1')
            return (1);
        i++;
    }
    return(MAP_NOT_CLOSED);
}

int    check_map(t_env *env)
{
    int i;
    int j;

    char **map;
    map = env->t_map.map;
    i = env->t_map.start_line; 
    find_start_end_lines(env, &env->t_map.start_line);
    //printf("t_map.i = %d\n\n", env->t_map.i);
    find_start_end_lines(env, &env->t_map.end_line);
    
    j = 0;
    while (map[i] && j <= env->t_map.end_line && line_closed(map[i]) == 1)
    {
        while (map[i][j])
        {
            if (ft_charset("012NSWE ", map[i][j]) == 0)
                return(MAP_ERROR_WRONG_CHAR);
            if (map[i][j] != '1')
                if ((map[i][j] == '2' || map[i][j] == '0') && (find_wall_down(map, i, j) == 0 || find_wall_up(map, i, j) == 0))
                    return (MAP_NOT_CLOSED);
            i++;
        }
        printf("line_closed(map[i]) = %d\n", line_closed(map[i]));
        i++;
    }
    // find_start_line(env);
    // find_last_line(env);
    
    printf("env->t_map.start_line = '%s'\n", env->t_map.map[env->t_map.start_line]);
    printf("env->t_map.end_line = '%s'\n", env->t_map.map[env->t_map.end_line]);
    // if (env->t_error == SUCCESS)
    //     check_middle_lines(env);
    return(1);
}