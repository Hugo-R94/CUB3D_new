/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:09:31 by hugz              #+#    #+#             */
/*   Updated: 2025/11/24 by assistant                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 

static float calc_distance(t_data *data, float x, float y)
{
    float dx;
    float dy;

    dx = x - data->player.px;
    dy = y - data->player.py;
    return (sqrt(dx * dx + dy * dy));
}

static float get_angle_to_sprite(t_data *data, float x, float y)
{
    float dx;
    float dy;
    float angle_to_sprite;
    float relative_angle;

    dx = x - data->player.px;
    dy = y - data->player.py;
    angle_to_sprite = atan2(dy, dx);
    relative_angle = angle_to_sprite - data->player.pa;
    while (relative_angle > M_PI)
        relative_angle -= 2 * M_PI;
    while (relative_angle < -M_PI)
        relative_angle += 2 * M_PI;
    return (relative_angle);
}

static int get_screen_x(float relative_angle, float fov)
{
    return ((int)((relative_angle / fov + 0.5) * 640));
}

static int get_tex_coord(int screen, int start, float ratio, int max)
{
    int coord;

    coord = (int)((screen - start) * ratio);
    if (coord < 0)
        coord = 0;
    if (coord >= max)
        coord = max - 1;
    return (coord);
}

static void draw_sprite_column(t_data *data, t_txt *tex, int x, int bounds[7])
{
    int         y;
    int         tex_x;
    int         tex_y;
    int         color;
    int         index;
    float       ratios[2];

    ratios[0] = (float)tex->img.width / (float)bounds[1];
    ratios[1] = (float)tex->img.height / (float)bounds[0];
    tex_x = get_tex_coord(x, bounds[2], ratios[0], tex->img.width);
    y = bounds[4] - 1;
    while (++y < bounds[5])
    {
        if (y < 0 || y >= data->render_gmp->height)
            continue;
        tex_y = get_tex_coord(y, bounds[4], ratios[1], tex->img.height);
        color = get_pixel(&tex->img, tex_x, tex_y);
        if (color != 0x000000)
        {
            index = y * data->render_gmp->width + x;
            if (index >= 0 && index < data->render_gmp->width
                * data->render_gmp->height)
            {
                if (data->render_gmp->pixels[index].type == PX_EMPTY
                    || (float)bounds[6] / 1000.0f < data->render_gmp->pixels[index].depth)
                {
                    data->render_gmp->pixels[index].color = color;
                    data->render_gmp->pixels[index].type = PX_MOB;
                    data->render_gmp->pixels[index].depth = (float)bounds[6] / 1000.0f;
                }
            }
        }
    }
}

static void render_sprite_columns(t_data *data, t_txt *tex, int bounds[7])
{
    int x;

    x = bounds[2] - 1;
    while (++x < bounds[3])
    {
        if (x >= 0 && x < data->render_gmp->width)
            draw_sprite_column(data, tex, x, bounds);
    }
}

static void calc_sprite_bounds(t_data *data, float params[3], int bounds[7])
{
    int full_height;
    int center_y;

    bounds[1] = (int)(data->render_gmp->height / params[2] * params[1]);
    bounds[0] = (int)(data->render_gmp->height / params[2] * params[1]);
    full_height = (int)(data->render_gmp->height / params[2]);
    center_y = (data->render_gmp->height / 2) + data->tilt
        + data->player.pl_height;
    bounds[5] = center_y + (full_height / 2);
    bounds[4] = bounds[5] - bounds[0];
    bounds[2] = get_screen_x(params[0], data->fov) - bounds[1] / 2;
    bounds[3] = bounds[2] + bounds[1];
    bounds[6] = (int)(params[2] * 1000);
}

void draw_sprite(t_data *data, float pos[2], char *sprite_name, float size)
{
    float   distance;
    float   relative_angle;
    int     bounds[7];
    t_txt   *tex;
    float   params[3];

    distance = calc_distance(data, pos[0], pos[1]);
    
    if (distance < 0.1f)
    {
        return ;
    }
    if (distance > 25.5)
    {
        return ;
    }
    
    relative_angle = get_angle_to_sprite(data, pos[0], pos[1]);
    
    if (fabs(relative_angle) > data->fov / 2)
    {
        return ;
    }
    tex = find_texture(data->txt, sprite_name);
    if (!tex)
    {
        return ;
    }
    params[0] = relative_angle;
    params[1] = size;
    params[2] = distance;
    calc_sprite_bounds(data, params, bounds);
    render_sprite_columns(data, tex, bounds);
}

#endif