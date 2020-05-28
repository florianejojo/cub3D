


// 1 regarder si la map est bien fermée par des 1 --> Le faire après avoir stocké la map dans double tableau 
// 2 regarder si la map contient uniquement les 4 caractères : 0, 1,2,N,S,E,W
// La description de la carte sera toujours en dernier dans le fichier, le reste des éléments peut être dans n’importe quel ordre.
// Mis à part la description de la map, chaque type d’élément peut être séparé par une ou plusieurs lignes vides.
// Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s).
// le parsing de la map doit prendre en compte les espaces


// --> 1 - ranger le fichier text dans un double tableau.
// --> 2 - Ranger les éléments dans la structure 
//              "FULL_ELEMENTS_DETECTED" != 1 ou que 
//              "TAB_ELEMENTS OK" != 1 (quand j'ai toutes les lettres et que je renconte un "\n")
//               si la lettre fait partie du charset, envoyer la lettre dans une fonction + mettre la lettre à 1
//--> Parcourir la ligne à chaque fois pour mettre à jour les stuctures
//--> A chaque nouvelle lettre je mets la lettre de la structure éléments à 1, et je check si FULL_ELEMENTS _DETECTED = 1. 
//       
//              Si l'élément est déjà à 1 : Je renvoi error
//
// --> Lire tant que c'est un \n
// --> Si c'est plus un \n, utiliser GNL et stocker la ligne à chaque fois dans un tableau de la structure.

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

void    ft_make_tab(t_env *env)
{
    int     fd;
    int     ret;
    char    buf[10];
    char    *str;
    int     i;
    i = 0;
    ft_bzero(env, sizeof(t_env));
    fd = open("maps/sujet.cub", O_RDONLY);
    while ((ret = read(fd, buf, 1)) > 0)                            // pour compter les chars
         env->t_map.nb_char++;
    str = (char*)malloc(sizeof(char)*(env->t_map.nb_char + 1 ));    // malloc de la chaine
    close (fd);
    fd = open("maps/sujet.cub", O_RDONLY);
    while ((ret = read(fd, buf, 1)) > 0)                            // pour remplir la chaine
     {
         str[i++] = buf[0];
       //  i++;
     }
    str[i] = '\0';
    env->t_map.map = ft_split(str, '\n');                           // pour créer un double tableau
    free (str);
}

//ft_pars_elem(t_env env)
// {
//     while (env->full_elements_detected )
// }
