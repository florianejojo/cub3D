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
    short                   R;              //pour savoir que la fonction parsing de la lettre a bien fonctionné
    short					textures;
    short                   F;
    short                   C;
}                           t_check;

typedef enum                s_error
{
	SUCCESS,					//Si tous les éléments de t_check sont à 1
	ERROR_INVALID_ELEMENTS,
	MAP_NOT_CLOSED,
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

// typedef struct				s_elements
// {
// //	char					*r;
// 	char					*n;
// 	char					*s;
// 	char					*w;
// 	char					*e;
// 	char					*nw;
// 	char					*ne;
// 	char					*sw;
// 	char					*se;
// 	char					*f;
// 	char					*c;
// }							t_elements;

typedef struct				s_rgb
{
	unsigned int			r;
	unsigned int			g;
	unsigned int			b;
}							t_rgb;

typedef struct				s_colors
{

	t_rgb				t_rgb_C;
	t_rgb				t_rgb_F;

}							t_colors;

                        

typedef	struct				s_res
{
	int						width;
	int						height;

}							t_res;

typedef	struct				s_textures_path
{
	char					*NO;
	char					*SO;
	char					*WE;
	char					*EA;
	char					*S;
}							t_textures_path;

typedef struct              s_map
{
    char					**map;
	int						nb_lines;
	int						nb_char;
	int						i;
	int 					j;
	int 					start_line;
	int						end_line;
}							t_map;

typedef	struct				s_env // définie par "env"
{
    t_textures_path         t_textures_path;
	t_map					t_map;
	t_colors				t_colors;
	t_res 					t_res;
	t_check					t_check;
	t_error					t_error; 
	

}							t_env;

void    make_tab(char *file, t_env *env);
void    pars_textures(t_env *env, int i, int j);
void    pars_resolution(t_env *env, int i, int j);
void    pars_colors(t_env *env, int i, int j);
void    parsing();
void    pars_elem(t_env *env);
void  	pars_colors(t_env *env, int i, int j);
void	check_map(t_env *env);
void    check_first_line(t_env *env);
#endif