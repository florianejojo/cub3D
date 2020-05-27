


// 1 regarder si la map est bien fermée par des 1 --> Le faire après avoir stocké la map dans double tableau 
// 2 regarder si la map contient uniquement les 4 caractères : 0, 1,2,N,S,E,W
// La description de la carte sera toujours en dernier dans le fichier, le reste des éléments peut être dans n’importe quel ordre.
// Mis à part la description de la map, chaque type d’élément peut être séparé par une ou plusieurs lignes vides.
// Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s).
// le parsing de la map doit prendre en compte les espaces


// --> 1- lire le fichier .cub et ranger les lignes qui commancent par des lettres dans la structure
// en  utilisant GNL tant que en mettant al ligne dans une structure à chaque fois pour la parser.
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

// ft_recup_tab (t_visu env)
// {
//     int ret;
//     while (ret > 0)
//     {
//         read
//     }
// }


// ft_pars_elem(t_visu env)
// {
//     char *line;

// }

// ft_pars_map(t_visu env)
// {

// }

// void    ft_tmap_parsing()
// {
//     t_visu env;
//     ft_bzero(env);
//     t_tmap->tmap = ft_recup_tmap(env);

    //if (ft_pars_elem(env) != 1)
    //    return ("ERROR_INVALID_ELEMENTS");
   // if (ft_pars_map(env) != 1)
   //     return ("ERROR_MAP");
    
//}