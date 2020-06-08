#include "../includes/cub3d.h"

//regarder si la map est bien fermée par des 1 --> Le faire après avoir stocké la map dans double tableau, (fait)
//regarder si la map contient uniquement les 4 caractères : 0, 1,2,N,S,E,W

// #pour checker la map:
// #une fonction pour trouver la position de la première ligne et la dernière ligne. OK
// une fonction check charset "0, 1,2,N,S,E,W" OK mettre une fonction charset dans la libft
// #une fonction qui regarde en fonction du char (au dessus, en dessous, a droite, a gauche), seulement si c'est pas un 1.
//  puis qui regarde avec des conditions pour si c'est la première ligne (alors c'est normal que au dessus ca existe pas) et dernière ligne(alors c'est normal que en dessous ca existe pas).


int check_around(t_env *env, int i, int j)
{
    if (env->t_map.map[i][j] == ' ')
    {
        if 
        ((env->t_map.map[i + 1][j] != '1' && env->t_map.map[i + 1][j] != ' ' && env->t_map.map[i + 1]) || (env->t_map.map[i - 1][j] != '1' && env->t_map.map[i - 1][j] != ' ' && env->t_map.map[i - 1]))
        {
            // env->t_error = MAP_NOT_CLOSED;
            return(0);
        }
        else if (((env->t_map.map[i][j + 1] != '1') && (env->t_map.map[i][j + 1] != ' ') && (env->t_map.map[i][j + 1])) || ((env->t_map.map[i][j - 1] != '1') && (env->t_map.map[i][j - 1] != ' ') && (env->t_map.map[i][j + 1])))
        {
            // env->t_error = MAP_NOT_CLOSED;
            return(0);
        }
    }
    return(1);
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
// void find_start_line(t_env *env) // + tu comptes les lignes
// {
//     int j;

//     j = 0;
//     while (env->t_map.map[env->t_map.i] && env->t_map.start_line == 0)
//     {
//         j = 0;
//         while (env->t_map.map[env->t_map.i][j] && env->t_map.start_line == 0)
//         {
//             if (env->t_map.map[env->t_map.i][j] != ' ')
//                 env->t_map.start_line = env->t_map.i;
        
//             j++;
    
//         }
//         env->t_map.i++;
//     }
// }
// void find_last_line(t_env *env)
// {
//    int j;

//     while (env->t_map.map[env->t_map.i + 1])
//         env->t_map.i++;
//     while (env->t_map.end_line == 0 && env->t_map.map[env->t_map.i])
//     {
//         j = 0;
//         while (env->t_map.end_line == 0 && env->t_map.map[env->t_map.i][j])
//         {
//             if (env->t_map.map[env->t_map.i][j] != ' ')
//                 env->t_map.end_line = env->t_map.i;
//             j++;
//         }
//         env->t_map.i--;
//     }

// }
void check_middle_lines(t_env *env)
{
    int j;
    int i;

    j = 0;
    i = env->t_map.start_line + 1;
    while (env->t_map.map[i])
    {
        while (env->t_map.map[i][j])
        {
            if (env->t_map.map[i][j] == ' ')
            {
                if ((env->t_map.map[i + 1][j] != '1' && env->t_map.map[i + 1][j] != ' ') || (env->t_map.map[i - 1][j] != '1' && env->t_map.map[i - 1][j] != ' '))
                    env->t_error = MAP_NOT_CLOSED;
                else if (((env->t_map.map[i][j + 1] != '1') && (env->t_map.map[i][j + 1] != ' ') && (env->t_map.map[i][j + 1] != '\0')) || ((env->t_map.map[i][j - 1] != '1') && (env->t_map.map[i][j - 1] != ' ') && (env->t_map.map[i][j + 1] != '\0')))
                    env->t_error = MAP_NOT_CLOSED;
            }
            j++;
        }
        i++;
    }
}

void check_map(t_env *env)
{
    
    find_start_end_lines(env, &env->t_map.start_line);
    //printf("t_map.i = %d\n\n", env->t_map.i);
    find_start_end_lines(env, &env->t_map.end_line);
    
    // find_start_line(env);
    // find_last_line(env);
    
    printf("env->t_map.start_line = '%s'\n", env->t_map.map[env->t_map.start_line]);
    printf("env->t_map.end_line = '%s'\n", env->t_map.map[env->t_map.end_line]);
    // if (env->t_error == SUCCESS)
    //     check_middle_lines(env);
}