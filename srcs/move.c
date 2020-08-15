#include "../includes/cub3d.h"

void    forward(t_env *env) //
{
    if (env->t_map.map[(int)env->ray.pos.x][(int)(env->ray.pos.y + env->ray.dir.y * env->ray.speed)] == '0')
		env->ray.pos.x += env->ray.dir.x * env->ray.speed;
	if (env->t_map.map[(int)(env->ray.pos.x + env->ray.dir.x * env->ray.speed)][(int)env->ray.pos.y] == '0')
		env->ray.pos.y += env->ray.dir.y * env->ray.speed;
}

void	move(t_env *env)
{
	if (env->mvt.up == 1)
		forward(env);
	// if (env->mvt.lft == 1)
	// 	backward(env);
}