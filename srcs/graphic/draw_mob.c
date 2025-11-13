/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:44:02 by hugz              #+#    #+#             */
/*   Updated: 2025/11/13 17:15:45 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float calculate_mob_distance(t_data *data, int i)
{
    float dx;
    float dy;

    dx = data->mob[i].mx - data->player.px;
    dy = data->mob[i].my - data->player.py;
    return (sqrt(dx * dx + dy * dy));
}

static float get_relative_angle(t_data *data, int i)
{
    float dx;
    float dy;
    float angle_to_mob;
    float relative_angle;

    dx = data->mob[i].mx - data->player.px;
    dy = data->mob[i].my - data->player.py;
    angle_to_mob = atan2(dy, dx);
    relative_angle = angle_to_mob - data->player.pa;
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
static void draw_mob_column(t_data *data, t_txt *tex, int x, int *bounds, int depth)
{
	int y;
	int tex_x;
	int tex_y;
	int color;
	int index;

	// Coordonnée de texture horizontale
	tex_x = get_tex_coord(x, bounds[2], 250.0 / bounds[1], 250);

	y = bounds[4] - 1;
	while (++y < bounds[5])
	{
		if (y < 0 || y >= data->render_gmp->height)
			continue;

		// Coordonnée de texture verticale
		tex_y = get_tex_coord(y, bounds[4], 250.0 / bounds[0], 250);
		color = get_pixel(&tex->img, tex_x, tex_y);

		// Ignore les transparents
		if (color != 0x000000)
		{
			index = y * data->render_gmp->width + x;
			if ((index >= 0 && index < data->render_gmp->width * data->render_gmp->height
				&& depth < data->render_gmp->pixels[index].depth) && (data->render_gmp->pixels[index].type != PX_EMPTY))
			{
				data->render_gmp->pixels[index].color = color;
				data->render_gmp->pixels[index].depth = depth;
				data->render_gmp->pixels[index].type = PX_MOB;
			}
            if (data->render_gmp->pixels[index].type == PX_EMPTY)
            {
				data->render_gmp->pixels[index].color = color;
				data->render_gmp->pixels[index].depth = depth;
				data->render_gmp->pixels[index].type = PX_MOB;
			}
		}
	}
}

static void draw_mob_sprite(t_data *data, t_txt *tex, int *bounds, int depth)
{
	int x;

	x = bounds[2] - 1;
	while (++x < bounds[3])
	{
		if (x < 0 || x >= data->render_gmp->width)
			continue;
		draw_mob_column(data, tex, x, bounds, depth);
	}
}

void draw_single_mob(t_data *data, int i)
{
	float distance;
	float relative_angle;
	int bounds[6];
	t_txt *mob_tex;
	int depth;

	distance = calculate_mob_distance(data, i);
	if (distance < 0.1f)
		return;
	relative_angle = get_relative_angle(data, i);
	if (fabs(relative_angle) > data->fov / 2)
		return;

	// Taille à l'écran
	bounds[0] = (int)(480 / distance);
	bounds[1] = bounds[0];
	bounds[4] = (480 / 2) - (bounds[0] / 2) + data->tilt + data->player.pl_height + 20;
	bounds[5] = bounds[4] + bounds[0];
	bounds[2] = get_screen_x(relative_angle, data->fov) - bounds[1] / 2;
	bounds[3] = bounds[2] + bounds[1];

	mob_tex = find_texture(data->txt, "mob");
	if (!mob_tex)
		return;

	// profondeur pour ce mob
	depth = distance;

	draw_mob_sprite(data, mob_tex, bounds, depth);
}

void draw_mobs(t_data *data)
{
	int i;

	i = 0;
	while (i < 4 && data->mob[i].mx != 0)
	{
		if (data->mob[i].is_alive)
			draw_single_mob(data, i);
		i++;
	}
}
