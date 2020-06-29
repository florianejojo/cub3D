#include "includes/cub3d.h"


int main (int argc, char **argv)
{
    int i;

    i = 0;
    
    t_env  *env;
    env = malloc(sizeof(t_env));
    ft_bzero(env, sizeof(t_env));

    env->t_error = init_map(argv[1], env);
    print_error(env->t_error);
    
    printf("\n\n");
    printf("env->t_res.height = %d, env->t_res.width = %d \n",env->t_map.t_res.height, env->t_map.t_res.width);
    
    printf("env->t_textures_path.NO = '%s'\nenv->t_textures_path.SO = %s\nenv->t_textures_path.WE = %s\nenv->t_textures_path.EA = %s\nenv->t_textures_path.S = %s\n",env->t_textures_path.NO, env->t_textures_path.SO, env->t_textures_path.WE, env->t_textures_path.EA, env->t_textures_path.S);
    
    printf("env->t_colors.t_rgb_F.r = %d\nenv->t_colors.t_rgb_F.g = %d\nenv->t_colors.t_rgb_F.b = %d\nenv->t_colors.t_rgb_C.r = %d\nenv->t_colors.t_rgb_C.g = %d\nenv->t_colors.t_rgb_C.b = %d\n",env->t_colors.rgb_F.r, env->t_colors.rgb_F.g, env->t_colors.rgb_F.b, env->t_colors.rgb_C.r, env->t_colors.rgb_C.g, env->t_colors.rgb_C.b);
    printf ("\n --------------------------------------- MAP : \n");
    
    // while (env->t_map.map[i])
    // {
    //     printf("'%s'", env->t_map.map[i]);
    //     printf("\n");
    //     i++;
    // }
    free(env);
    //return (1);
}