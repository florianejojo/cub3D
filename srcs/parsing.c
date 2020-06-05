


// 1 regarder si la map est bien fermée par des 1 --> Le faire après avoir stocké la map dans double tableau 
// 2 regarder si la map contient uniquement les 4 caractères : 0, 1,2,N,S,E,W
// La description de la carte sera toujours en dernier dans le fichier, le reste des éléments peut être dans n’importe quel ordre.
// Mis à part la description de la map, chaque type d’élément peut être séparé par une ou plusieurs lignes vides.
// Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s).
// le parsing de la map doit prendre en compte les espaces


// --> 1 - ranger le fichier text dans un double tableau.
// --> 2 - Ranger les éléments dans la envcture 
//              "FULL_ELEMENTS_DETECTED" != 1 ou que 
//              "TAB_ELEMENTS OK" != 1 (quand j'ai toutes les lettres et que je renconte un "\n")
//               si la lettre fait partie du charset, envoyer la lettre dans une fonction + mettre la lettre à 1
//--> Parcourir la ligne à chaque fois pour mettre à jour les stuctures
//--> A chaque nouvelle lettre je mets la lettre de la envcture éléments à 1, et je check si FULL_ELEMENTS _DETECTED = 1. 
//       
//              Si l'élément est déjà à 1 : Je renvoi error
//
// --> Lire tant que c'est un \n
// --> Si c'est plus un \n, utiliser GNL et stocker la ligne à chaque fois dans un tableau de la envcture.

// 

// --> Quand FULL ELMENTRS DETECTED = 1, je cherche la première ligne avec un char
//              si c'est un 1, continuer,
//              sinon renvoyer "error car pas de 1"
// --> Ranger la map dans un double tableau
//              checker le char à chaque fois pour voir s'il est dans le charset "0, 1,2,N,S,E,W + espace" (faire une fonction dédiée pour espace peut être ?)
//              si un char est pas dans charset renvoyer une erreur
//              si open = 0 alors fin de fichier
// --> Parcourir la map pour voir si elle est bien fermée et si elle commence bien par un 1

#include "../includes/cub3d.h"

void    make_tab(char *file, t_env *env)
{
    int     fd;
    int     ret;
    char    buf[10];
    char    *str;
    int     i;
    i = 0;
            

    if ((fd = open(file, O_RDONLY)) < 0)
        printf("fd = %d\n", fd);
    while ((ret = read(fd, buf, 1)) > 0)                           // pour compter les chars
         env->t_map.nb_char++;
    str = (char*)malloc(sizeof(char)*(env->t_map.nb_char + 1 ));    // malloc de la chaine
    close (fd);
    fd = open(file, O_RDONLY);
    while ((ret = read(fd, buf, 1)) > 0)                            // pour remplir la chaine
         str[i++] = buf[0];
    str[i] = '\0';
    env->t_map.map = split(str, '\n');                           // pour créer un double tableau
    close (fd);
    free (str);                                                     // maintenant il y a 2 trucs mallocs: env + double tableau **map
}

void    pars_resolution(t_env *env, int i, int j)
{
    while (env->t_map.map[i][j] == ' ')
        j++;
    while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
        env->t_res.width = env->t_res.width * 10 + env->t_map.map[i][j] - 48; 
        j++;
    }
    while (env->t_map.map[i][j] == ' ')
        j++;
    while (env->t_map.map[i][j] >= '0' && env->t_map.map[i][j] <= '9')
    {
        env->t_res.height = env->t_res.height * 10 + env->t_map.map[i][j] - 48; 
        j++;
    }
    while (env->t_map.map[i][j] == ' ')
        j++;
    if (env->t_map.map[i][j] != '\0' || env->t_res.width <= 0 || env->t_res.height <= 0)
        env->t_error = ERROR_INVALID_ELEMENTS;
}

int		charset(char c) // a mettre dans ma libft ?
{
	int		i;
    char    *charset;

	i = 0;
    charset = "RNSWEFC";
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void    pars_elem(t_env *env)
{
    int i;

    i = 0;
    while (charset(env->t_map.map[i][0]) == 1)
    { 
            if (env->t_map.map[i][0] == 'R')
                pars_resolution(env, i, 1);
            else if (env->t_map.map[i][0] == 'F' || env->t_map.map[i][0] == 'C')
                 pars_colors(env, i, 1);
            else
                pars_textures(env, i, 2);
    }
    i++;
    env->t_map.i = i; // on choppe la ligne après tous les éléments
}

void       check_first_line(t_env *env) // + tu comptes les lignes
{
    int j;

    j = 0;
    while (env->t_map.map[env->t_map.i][j] == ' ')
    {
        if (env->t_map.map[env->t_map.i][j] == '\0')
           env->t_map.i++;
        j++;
    }
    env->t_map.start_line = env->t_map.i;
    while (env->t_map.map[env->t_map.start_line][j])            // là je sais qu'il y a que des 1 en haut
	{
		if (env->t_map.map[env->t_map.start_line][j] != '1')
			env->t_error = MAP_NOT_CLOSED;
		j++;
	}

}
void        check_last_line(t_env *env)
{
    int j;

    j = 0;
    while (env->t_map.map[env->t_map.i][0]) // Je veux trouver le nombre de lignes, ou la dernière ligne 
        env->t_map.i++; // là j'arrive à la fin du fichier
    while (env->t_map.map[env->t_map.i][j] == ' ')
    {
        if (env->t_map.map[env->t_map.i][j] == '\0')
           env->t_map.i--;
        j++;
    }
    env->t_map.end_line = env->t_map.i;
    while (env->t_map.map[env->t_map.end_line][j])            // là je sais qu'il y a que des 1 en haut
	{
		if (env->t_map.map[env->t_map.end_line][j] != '1')
			env->t_error = MAP_NOT_CLOSED;
		j++;
	} 
}
void    check_middle_lines(env)
{
        
}

void		check_map(t_env *env)
{
	int j;
    int i;

	j = 0;
    i = env->t_map.start_line;
    check_first_line(env);
    check_last_line(env);
    while (env->t_error == SUCCESS && env->t_map.map[i])
    {
        check_middle_lines(env);
        i++;
    }
}

void		closed_map(t_env *env)
{
    int i;
	int j;

    i = env->t_map.i;
	j = 0;
	while (env->t_map.map[i][j])            // là je sais qu'il y a que des 1 en haut
	{
		if (env->t_map.map[i][j] != '1')
			env->t_error = MAP_NOT_CLOSED;
		j++;
	}
	j = 0;
    while (env->t_map.map[i][j])
    {
        if (env->t_map.map[i][j] != '1' || env->t_map.map[i][j] != ' ')
			env->t_error = MAP_NOT_CLOSED;
        env->t_map.nb_lines++;
        i++;
    }
	while (env->t_map.map[env->t_map.nb_lines - 1][j])
	{
		if (env->t_map.map[env->t_map.nb_lines - 1][j] != '1')
			env->t_error = MAP_NOT_CLOSED;
		j++;
	}
}

// void    parsing()
// {
// // int i;

// //     i = 0;
//     t_env  *env;
//     env = malloc(sizeof(t_env));
//     bzero(env, sizeof(t_env));
//     //void	(*tab_fct[8])(t_env*, int);
//     //init_tab_fct(env);
//     make_tab(env);
//     pars_elem(env);
//     printf("env->t_res.width= %d, env->t_res.height= %d\n",env->t_res.width, env->t_res.height);
//    // free(env->t_elements.NO);
//     free(env);
    
// }

