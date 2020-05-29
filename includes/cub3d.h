#ifndef CUB3D_H
# define CUB3D_H
//https://github.com/hbrulin/Cub3D/blob/master/cub.h exemple de structure

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> //read
#include <stdio.h> //printf

#include "../libft/libft.h"



typedef struct              s_check
{
    short                   full_elements_detected;
    short                   tab_elements_ok;
    short                   r;              //pour mettre à 1 les lettres quand je les trouve
    short                   no;
    short                   se;
    short                   we;
    short                   ea;
    short                   s;
    short                   f;
    short                   c;
}                           t_check;

typedef enum                s_error
{
	SUCCESS,
	ERROR_INVALID_ELEMENTS,
	MAP_ERROR_NOT_CLOSED,
    MAP_ERROR_WRONG_CHAR,
    ERROR_INVALID_FILE, // si c'est pas .cub

	//WRONG_INPUT,
	//MALLOC_FAIL,
	//IMG_FAIL,
	//OPEN_ERR,
	//MLX_FAIL,
	//WRITE_FAIL,
	//WRONG_TEX
}						    t_error;

typedef struct				s_elements
{
	char					*r;
	char					*n;
	char					*s;
	char					*w;
	char					*e;
	char					*nw;
	char					*ne;
	char					*sw;
	char					*se;
	char					*f;
	char					*c;
}							t_elements;

typedef struct				s_colors
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
}							t_colors;

typedef struct              s_map
{
    char					**map;
	int						nb_line;
	int						nb_char;
	int						index;
	char					tab_index[9]; // A voir combien d'index
	void					(*tab_fct[8])(t_env*, int); // a voir combien de fonctions en fonctions de l'index
}                           t_map;

typedef	struct				s_res
{
	int						h
}							t_res;

typedef	struct				s_env // déifnie par "env"
{
    t_elements              t_elements;
	t_map					t_map; // (élements + map)
	t_colors				t_floor_color;
	t_colors				t_ceiling_color;
	t_res 					t_res;
	t_check					t_check;

}							t_env;


void    ft_make_tab(t_env *env);

#endif