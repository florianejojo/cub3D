#ifndef CUB3D_H
# define CUB3D_H
//https://github.com/hbrulin/Cub3D/blob/master/cub.h exemple de structure

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> //read
#include <stdio.h> //printf
#include "../minilibx_mms_20200219/mlx.h"

#include "../libft/libft.h"

# include "keycode.h"
# include "mlx.h"
#include <math.h>



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
	SUCCESS,
	INVALID_ELEMENTS, // == 0
	LINE_NOT_CLOSED,
	MAP_NOT_CLOSED,
    WRONG_CHAR,
	MAP_ERROR,
    INVALID_FILE, // si c'est pas .cub
	MALLOC_FAILED,
	FILE_NOT_OPENED,
	NO_PLAYER_POS,
	TO_MANY_PLAYER_POS,
	ERROR_RES,
	ERROR_COLORS,
	INVALID_TEXTURES,
	ERROR_PARSING,
	ERROR_START_END,
	MLX_FAIL,
}						    t_error;

typedef struct				s_rgb
{
	unsigned int			r;
	unsigned int			g;
	unsigned int			b;
}							t_rgb;

typedef struct				s_colors
{

	t_rgb				rgb_C;
	t_rgb				rgb_F;

}							t_colors;

typedef struct  s_img {
    void      	  			*ptr;
    char        			*addr;
    int         			bits_pp;
    int         			line_length;
    int         			endian;
}               t_img;

//  typedef struct	s_img
// {
// 	void  *img;      /* pointer qui permet d'identifier l'image */
// 	char  *img_str;  /* string contenant tous les pixels de l'image */
// 	int   bits;      /* nombre de bits par pixels */
// 	int   size_line; /*  taille de la img_str*/
// 	int   endian;    /* permet de signifier la fin d'une image*/
// }               t_img;                       

typedef struct				s_coord
{
	float					x;
	float					y;
}							t_coord;

typedef struct				s_ray
{
	t_coord					pos; //(est-ce que je n’irai pas remplir directement ici au lieu de player_pos_x et y) c'est fait dans init ray
	t_coord					dir;
	t_coord					plane;
	float					*buff;
	t_coord					camera;
	t_coord					raydir;
	float					speed;
	t_coord					deltadist;
	t_coord					step;
	int						hit; //was there a wall hit?
	int						side; //was a NS or a EW wall hit?


}							t_ray;

typedef	struct				s_res
{
	int			width;
	int			height;

}							t_res;

typedef	struct				s_textures_path
{
	char					*NO;
	char					*SO;
	char					*WE;
	char					*EA;
	char					*S;
}							t_textures_path;

typedef struct              s_map // tout ce que je pars grâce au fichier 
{
    char					**map;
	int						nb_lines;
	int						nb_char;
	t_res 					res;
	int						i;
	int 					j;
	int 					start_line;
	int						end_line;
	char					player_dir;
	// int						player_dir_x;	
	// int						player_dir_y;
	int						player_pos_x; //je le remplis au moment du parsing de la Map 
	int						player_pos_y; //je le remplis au moment du parsing de la Map 
	// int						pos_y;
	// int						error;
}							t_map;

typedef struct 				s_mvt
{
	int						up;
	int						dwn;
	int						lft;
	int						rgt;
}							t_mvt;


typedef	struct				s_env // définie par "env"
{
    t_textures_path         t_textures_path;
	t_map					t_map;
	t_colors				t_colors;
	t_check					t_check;
	t_error					t_error;
	int						error_type;
	t_ray					ray;
	void					*mlx_ptr;
	void					*win_ptr;
	t_img	 				img;
	t_mvt 					mvt;
	

}							t_env;


char	**ft_split_cub(t_env *env, char const *s, char c);
int 	make_map(char *file, t_env *env);
void    make_tab(char *file, t_env *env);
int 	check_textures(t_env *env);
int    	pars_textures(t_env *env, int i, int j);
int    	pars_resolution(t_env *env, int i, int j);
int    	pars_colors(t_env *env, int i, int j);
void    parsing();
int     pars_map(t_env *env);
int		check_map(t_env *env);
void    check_first_line(t_env *env);
void	print_error(int error);
int 	skip_wsp(int i, int j, t_env *env);
int		find_wall_up(t_env *env, int i, int j);
int		find_wall_down(t_env *env, int i, int j);
int     init_map(char *file, t_env *env);
int     line_closed(char *line);
int 	is_wsp(int i, int j, t_env *env);
int 	init_ray(t_env *env);
int		ray(t_env *env);
void	moves(t_env *env);
int		ft_new_image(t_env *env, int width, int height);

#endif