
#include "../includes_bonus/cub3d.h"

void  calc_horiz_line(t_env *env, int y)
{
        env->bonus.raydirx0 = env->ray.dir.x - env->ray.plane.x;
        env->bonus.raydiry0 = env->ray.dir.y - env->ray.plane.y;
        env->bonus.raydirx1 = env->ray.dir.x + env->ray.plane.x;
        env->bonus.raydiry1 = env->ray.dir.y + env->ray.plane.y;
        env->bonus.center_p = y - env->t_map.res.height / 2;
        env->bonus.pos_z = 0.5 * env->t_map.res.height;
        env->bonus.row_distance = env->bonus.pos_z / env->bonus.center_p;
        env->bonus.floor_step.x = env->bonus.row_distance * (env->bonus.raydirx1 - env->bonus.raydirx0) / env->t_map.res.width;
        env->bonus.floor_step.y = env->bonus.row_distance * (env->bonus.raydiry1 - env->bonus.raydiry0) / env->t_map.res.width;
        env->bonus.floor.x = env->t_map.player_pos.x + env->bonus.row_distance * env->bonus.raydirx0;
        env->bonus.floor.y = env->t_map.player_pos.y + env->bonus.row_distance * env->bonus.raydiry0;
}

void  calc_pix(t_env *env)
{
        env->bonus.cell.x = (int)(env->bonus.floor.x);
        env->bonus.cell.y = (int)(env->bonus.floor.y);
        env->bonus.t.x = (int)(env->tex_width * (env->bonus.floor.x - env->bonus.cell.x)) & (env->tex_width - 1);
        env->bonus.t.y = (int)(env->tex_height  * (env->bonus.floor.y - env->bonus.cell.y)) & (env->tex_height - 1);
        env->bonus.floor.x += env->bonus.floor_step.x;
        env->bonus.floor.y += env->bonus.floor_step.y;
        
}

int   draw_floor_and_ceiling(t_env *env)
{
    int y;
    int x;
  
    y = 0;
    x = 0;

    while (y <= env->t_map.res.height)
    {
        calc_horiz_line(env, y);
       
      while (x <= env->t_map.res.width)
      {
        calc_pix(env);
        env->bonus.color = env->bonus.floor_img->addr[env->tex_width * env->bonus.t.y + env->bonus.t.x];
        env->bonus.color = (env->bonus.color >> 1) & 8355711;
        env->img->addr[(y * env->t_map.res.width + x)] = env->bonus.color;
        env->bonus.color = env->bonus.ceiling_img->addr[env->tex_width * env->bonus.t.y + env->bonus.t.x];
        env->bonus.color = (env->bonus.color >> 1) & 8355711;
        env->img->addr[((env->t_map.res.height - y - 1) * env->t_map.res.width + x)] = env->bonus.color;
        x++;
      }
      x = 0;
      y++;
    }
    
    return (SUCCESS);
}