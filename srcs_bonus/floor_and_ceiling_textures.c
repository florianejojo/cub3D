
#include "../includes_bonus/cub3d.h"

int   draw_floor_and_ceiling(t_env *env)
{
 //FLOOR CASTING
    int y;
    int x;

    y = 0;
    x = 0;
    t_img *ceiling_img;
    t_img *floor_img;
    while (y < env->t_map.res.height)
    {
       
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
        env->bonus.raydirx0 = env->ray.dir.x - env->ray.plane.x;
        env->bonus.raydiry0 = env->ray.dir.y - env->ray.plane.y;
        env->bonus.raydirx1 = env->ray.dir.x + env->ray.plane.x;
        env->bonus.raydiry1 = env->ray.dir.y + env->ray.plane.y;

      // Current y position compared to the center of the screen (the horizon)
        env->bonus.center_p = y - env->t_map.res.height / 2;

      // Vertical position of the camera.
        env->bonus.pos_z = 0.5 * env->t_map.res.height;

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
        env->bonus.row_distance = env->bonus.pos_z / env->bonus.center_p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
        env->bonus.floor_step.x = env->bonus.row_distance * (env->bonus.raydirx1 - env->bonus.raydirx0) / env->t_map.res.width;
        env->bonus.floor_step.y = env->bonus.row_distance * (env->bonus.raydirx1 - env->bonus.raydiry0) / env->t_map.res.width;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
        env->bonus.floor.x = env->t_map.player_pos.x + env->bonus.row_distance * env->bonus.raydirx0;
        env->bonus.floor.y = env->t_map.player_pos.y + env->bonus.row_distance * env->bonus.raydiry0;
       
      while (x < env->t_map.res.width)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        env->bonus.cell.x = (int)(env->bonus.floor.x);
        env->bonus.cell.y = (int)(env->bonus.floor.y);

        // get the texture coordinate from the fractional part
        env->bonus.t.x = (int)(env->tex_width * (env->bonus.floor.x - env->bonus.cell.x)) & (env->tex_width - 1);
        env->bonus.t.y = (int)(env->tex_height  * (env->bonus.floor.y - env->bonus.cell.y)) & (env->tex_height - 1);

        env->bonus.floor.x += env->bonus.floor_step.x;
        env->bonus.floor.x += env->bonus.floor_step.y;
        
        // choose texture and draw the pixel
        if (!(ceiling_img = new_image(env, CEILING_TEXTURE_PATH)))
            return (IMG_FAIL);
        if(!(floor_img = new_image(env, FLOOR_TEXTURE_PATH)))
            return (IMG_FAIL);
        

        env->bonus.color = floor_img->addr[env->tex_width * env->bonus.t.x + env->bonus.t.y];
        printf("floor_img->addr[env->tex_width * env->bonus.t.y + env->bonus.t.x] = %d\n", floor_img->addr[env->tex_width * env->bonus.t.y + env->bonus.t.x]);
        env->bonus.color = (env->bonus.color >> 1) & 8355711;
        env->img->addr[(y * env->t_map.res.width + x)] = env->bonus.color;
        

        //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        env->bonus.color = ceiling_img->addr[env->tex_width * env->bonus.t.y + env->bonus.t.x]; 
        env->bonus.color = (env->bonus.color >> 1) & 8355711;
        env->img->addr[(env->t_map.res.height - y - 1) + x] = env->bonus.color;
        x++;
      }
      y++;
    }
    return (SUCCESS);
}