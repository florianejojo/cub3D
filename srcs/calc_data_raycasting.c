#include "../includes/cub3d.h"


void init_vectors(t_env *env, int x) // calcul de raydir avec les 2 vacteurs: plane et dir + camera
{

    env->ray.camera = 2 * x / (double)env->t_map.res.width - 1; //numéro de ligne verticale de pixels ou on est
    env->ray.raydir.x = env->ray.dir.x + env->ray.plane.x * env->ray.camera;
    env->ray.raydir.y = env->ray.dir.y + env->ray.plane.y * env->ray.camera;
//    printf("env->width= %d\n", env->t_map.res.width);
//     printf("env->ray.dir.x = %ff\n", env->ray.dir.x);
//     printf("env->ray.dir.y = %ff\n", env->ray.dir.y);
//     printf("env->ray.raydir.x = %ff\n", env->ray.raydir.x);
//     printf("env->ray.raydir.y = %ff\n", env->ray.raydir.y);
//     printf("env->ray.plane.x = %ff\n", env->ray.plane.x);
//     printf("env->ray.plane.y = %ff\n", env->ray.plane.y);
//     printf("env->ray.camera = %ff\n", env->ray.camera);
//     printf("--------------------------------------------\n");

    env->ray.map.x = (int)env->t_map.player_pos.x; // c'est fait dans init ray, j'ai stocké la variable position joueur x et y dans env->ray.pos.x et y
    env->ray.map.y = (int)env->t_map.player_pos.y;
    // printf("env->t_map.player_pos.x = %f\n", env->t_map.player_pos.x);
    // printf("env->t_map.player_pos.y = %f\n", env->t_map.player_pos.y);
    // printf("env->ray.map.x = %d\n", env->ray.map.x);
    // printf("env->ray.map.y = %d\n", env->ray.map.y);
    env->ray.deltadist.x = sqrt(1 + (env->ray.raydir.y * env->ray.raydir.y) /
		(env->ray.raydir.x * env->ray.raydir.x));
	env->ray.deltadist.y = sqrt(1 + (env->ray.raydir.x * env->ray.raydir.x) /
		(env->ray.raydir.y * env->ray.raydir.y));
	env->ray.hit = 0;
    // printf("env->ray.deltadist.x = %f\n", env->ray.deltadist.x);
    // printf("env->ray.deltadist.y = %f\n", env->ray.deltadist.y);
    //  printf("--------------------------------------------\n");

}

void calc_step(t_env *env)
{
    if (env->ray.raydir.x < 0) 
    {
        env->ray.step.x = -1;
        env->ray.sidedist.x = (env->t_map.player_pos.x - env->ray.map.x) * env->ray.deltadist.x;
        
    }
    else
    {
        env->ray.step.x = 1;
        env->ray.sidedist.x = (env->ray.map.x + 1.0 - env->t_map.player_pos.x) * env->ray.deltadist.x;
    }
    if (env->ray.raydir.y < 0)
    {
        env->ray.step.y = -1;
        env->ray.sidedist.y = (env->t_map.player_pos.y - env->ray.map.y) * env->ray.deltadist.y;
    }
    else
    {
        env->ray.step.y = 1;
        env->ray.sidedist.y = (env->ray.map.y + 1.0 - env->t_map.player_pos.y) * env->ray.deltadist.y;
        
    }
    // printf("env->ray.sidedist.x = %f\n", env->ray.sidedist.x);
    // printf("env->ray.sidedist.y = %f\n", env->ray.sidedist.y);
    // printf("env->ray.step.x = %f\n", env->ray.step.x);
    // printf("env->ray.step.y = %f\n", env->ray.step.y);
    //  printf("--------------------------------------------\n");
    env->check_calc = env->check_calc + 1; 

}

void    perform_DDA(t_env *env)
{
    while (env->ray.hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        // printf("env->ray.hit == %d\n", env->ray.hit == 0);
        if (env->ray.sidedist.x < env->ray.sidedist.y) // x-side hit --> mur est nord sud
        {
            env->ray.sidedist.x += env->ray.deltadist.x;
            
            env->ray.map.x += env->ray.step.x;
            
            env->ray.side = 0;
            
        }
        else                                            
        {
            env->ray.sidedist.y += env->ray.deltadist.y;
            env->ray.map.y = env->ray.map.y + env->ray.step.y;
            env->ray.side = 1;                                          //y-side hit --> Le mur est west east
            
        }
        
        //Check if ray has hit a wall
       if (env->t_map.map[env->ray.map.y][env->ray.map.x] != '0' && env->t_map.map[env->ray.map.y][env->ray.map.x] != '2')
        {
            
        //    printf("env->t_map.map[%d][%d] = %c\n", env->ray.map.y, env->ray.map.x, env->t_map.map[env->ray.map.y][env->ray.map.x]);
            env->ray.hit = 1;
        }
    }
    // printf("env->ray.hit apres while == %d\n", env->ray.hit == 0);
    // printf ("env->ray.map.x = %d\n", env->ray.map.x);
    // printf ("env->ray.map.y = %d\n", env->ray.map.y);
    // printf ("env->ray.side = %d\n", env->ray.side);
    // printf("--------------------------------------------\n");

    
}

void    calc_perpwalldist(t_env *env) // j'ai ajouté valeur absolue mais je sais pas si c'est nécessaire
{
    //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (env->ray.side == 0)
    {
        env->ray.perpwalldist = fabs((env->ray.map.x - env->t_map.player_pos.x + (1 - env->ray.step.x) / 2) / env->ray.raydir.x);
        // env->ray.perpwalldist = fabsf((env->ray.map.x - env->t_map.player_pos.x + (1 - env->rc.step.x) / 2) / env->rc.rdir.x);
    }
    else
    {
        env->ray.perpwalldist = fabs((env->ray.map.y - env->t_map.player_pos.y + (1 - env->ray.step.y) / 2) / env->ray.raydir.y);
    
    }
    // printf ("env->ray.perpwalldist = %f\n", env->ray.perpwalldist);
    // printf("--------------------------------------------\n");
}

void calc_draw_infos(t_env *env) // a Quel moment on calcule la hauteur du mur en pixels avec perwall dist ?
{
    //Calculate height of line to draw on screen
    env->ray.lineheight = fabs(env->t_map.res.height / env->ray.perpwalldist);
    //calculate lowest and highest pixel to fill in current stripe
    env->ray.drawstart = (-1 * env->ray.lineheight) / 2 + env->t_map.res.height / 2;
    if (env->ray.drawstart < 0)
        env->ray.drawstart = 0;

    env->ray.drawend = env->ray.lineheight / 2 + env->t_map.res.height / 2;
    if (env->ray.drawend >= env->t_map.res.height)
        env->ray.drawend = env->t_map.res.height - 1;
    env->check_calc = env->check_calc + 1; 
//     printf ("env->ray.drawstart = %d\n", env->ray.drawstart);
// printf ("env->ray.drawend = %d\n", env->ray.drawend);
    // printf ("env->ray.lineheight = %f\n", env->ray.lineheight);
    // printf ("env->t_map.res.height = %d\n", env->t_map.res.height);
    // printf ("env->ray.perpwalldist = %f\n", env->ray.perpwalldist);
    //     printf("--------------------------------------------\n");
    


}

void	calc_textures_data(t_env *env)
{
	// double wallx;
    // //texturing calculations
//       int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

	if (env->ray.side == 0)
		env->ray.wall.x = env->t_map.player_pos.y + env->ray.perpwalldist * env->ray.raydir.y;
	else
		env->ray.wall.x = env->t_map.player_pos.x + env->ray.perpwalldist * env->ray.raydir.x;
	env->ray.wall.x -= floor(env->ray.wall.x);
	env->ray.tex.x = (int)(env->ray.wall.x * (double)(TEXWIDTH));
	if ((env->ray.side == 0 && env->ray.raydir.x > 0) || (env->ray.side == 1 && env->ray.raydir.x < 0))
		env->ray.tex.x = TEXWIDTH - env->ray.tex.x - 1;
    
	env->ray.tex_step = 1.0 * TEXHEIGHT / env->ray.lineheight; // How much to increase the texture coordinate per screen pixel
	env->ray.tex_pos = (env->ray.drawstart - env->t_map.res.height / 2 + env->ray.lineheight / 2) * env->ray.tex_step; // Starting texture coordinate
;
    // printf ("env->ray.tex_step = %f\n", env->ray.tex_step);
    // printf ("env->ray.tex_pos = %f\n", env->ray.tex_pos);
    // printf ("env->ray.tex.x = %d\n", env->ray.tex.x);
}
     

int     calc_data_raycasting(t_env *env, int x)
{
        init_vectors(env, x); // Calculs OK -  ici on a, le numéro de ligne verticale de pixels ou on est, on a déjà initilaité plane et dir avant, maintenant on calcule raydir
        calc_step(env);
        perform_DDA(env);
        calc_perpwalldist(env);
        calc_draw_infos(env);
        calc_textures_data(env);
        // if (env->check_calc == 5 )
        //     return (SUCCESS);
        // else 
        //     return (CALC_RAY_FAIL);

        return (SUCCESS);
}