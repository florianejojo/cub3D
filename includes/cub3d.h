



#ifndef CUB3D_H
# define CUB3D_H
//https://github.com/hbrulin/Cub3D/blob/master/cub.h exemple de structure


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

typedef struct				s_elements_id
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
}							t_elements_id;

typedef struct				s_colors
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
}							t_colors;

typedef struct              s_map
{
    char					**tab_map;
	int						nb_line;
	int						nb_char;

}                           t_map;

typedef	struct				s_visu
{
    t_elements_id           elements;
	t_map					map;
	t_colors				floor_color;
	t_colors				ceiling_color;

}							t_visu;

#endif