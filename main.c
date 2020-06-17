#include "includes/cub3d.h"


int main (int argc, char **argv)
{
    int i;

    i = 0;
    
    t_env  *env;
    
    env = malloc(sizeof(t_env));
    
    ft_bzero(env, sizeof(t_env));
    
    make_tab(argv[1], env);
    
    pars_elem(env);
    
    // env->t_error = check_map(env);
    
    // print_error(env->t_error);
 
    

    
    // printf("env->t_res.height = %d, env->t_res.width = %d \n",env->t_res.height, env->t_res.width);
    // printf("env->t_textures_path.NO = '%s'\n, env->t_textures_path.SO= %s, env->t_textures_path.WE = %s, env->t_textures_path.EA = %s , env->t_textures_path.S = %s \n",env->t_textures_path.NO, env->t_textures_path.SO, env->t_textures_path.WE, env->t_textures_path.EA, env->t_textures_path.S);
    // printf("env->t_colors.t_rgb_F.r = %d, env->t_colors.t_rgb_F.g = %d , env->t_colors.t_rgb_F.b = %d, env->t_colors.t_rgb_C.r = %d, env->t_colors.t_rgb_C.g = %d, env->t_colors.t_rgb_C.b = %d\n",env->t_colors.t_rgb_F.r, env->t_colors.t_rgb_F.g, env->t_colors.t_rgb_F.b, env->t_colors.t_rgb_C.r, env->t_colors.t_rgb_C.g, env->t_colors.t_rgb_C.b);
    printf ("\n -------------------------- MAP : \n");
    
    while (env->t_map.map[i])
    {
        printf("'%s'", env->t_map.map[i]);
        printf("\n");
        i++;
    }
    free(env);
    //return (1);
}