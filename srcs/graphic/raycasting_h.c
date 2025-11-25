/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_h.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:13:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/24 15:25:02 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_horizontal_ray(t_data *data, t_raycast *ray, float angle)
{
	ray->atan = -1.0f / tan(angle);
	if (angle > M_PI)
	{
		ray->ry = (int)data->player.py - 0.0001f;
		ray->rx = (data->player.py - ray->ry) * ray->atan + data->player.px;
		ray->yo = -1.0f;
	}
	else
	{
		ray->ry = (int)data->player.py + 1.0f;
		ray->rx = (data->player.py - ray->ry) * ray->atan + data->player.px;
		ray->yo = 1.0f;
	}
	ray->xo = -ray->yo * ray->atan;
}

void	cast_horizontal_ray(t_data *data, float *rx, float *ry, float angle)
{
	t_raycast ray;
	int		dof;

	init_horizontal_ray(data, &ray, angle);
	dof = 0;
	while (dof < 100)
	{
		if (is_wall_hit(data, (int)ray.rx, (int)ray.ry))
			break ;
		ray.rx += ray.xo;
		ray.ry += ray.yo;
		dof++;
	}
	*rx = ray.rx;
	*ry = ray.ry;
}
// void cast_horizontal_door_ray(t_data *data, float *rx, float *ry, float angle)
// {
//     t_raycast   ray;
//     int         dof;
//     int         map_x;
//     int         map_y;
    
//     init_horizontal_ray(data, &ray, angle);
//     dof = 0;
//     while (dof < 25)
//     {
//         map_x = (int)ray.rx;
//         map_y = (int)ray.ry;
        
//         if (is_door_hit(data, map_x, map_y))
//         {
//             // Centre la porte sur Y (au milieu de la case)
//             *ry = (float)map_y + 0.5f;
//             *rx = ray.rx;
//             return;
//         }
//         ray.rx += ray.xo;
//         ray.ry += ray.yo;
//         dof++;
//     }
//     *rx = ray.rx;
//     *ry = ray.ry;
// }
#ifdef BONUS 

void cast_horizontal_door_ray(t_data *data, float *rx, float *ry, float angle)
{
    t_raycast   ray;
    int         dof;
    int         map_x;
    int         map_y;
    
    init_horizontal_ray(data, &ray, angle);
    dof = 0;
    while (dof < 25)
    {
        map_x = (int)ray.rx;
        map_y = (int)ray.ry;
        
        if (is_door_hit(data, map_x, map_y))
        {
            // Centre la porte sur Y ET ajuste X pour toucher le centre
            *ry = (float)map_y + 0.5f;
            // Recalcule rx pour qu'il corresponde au centre Y
            // rx = player.px + t * cos(angle), où t = (ry - player.py) / sin(angle)
            float t = (*ry - data->player.py) / sin(angle);
            *rx = data->player.px + t * cos(angle);
            return;
        }
        ray.rx += ray.xo;
        ray.ry += ray.yo;
        dof++;
    }
    *rx = ray.rx;
    *ry = ray.ry;
}
void cast_horizontal_mob_ray(t_data *data, float *rx, float *ry, float angle)
{
    t_raycast   ray;
    int         dof;
    int         map_x;
    int         map_y;
    
    init_horizontal_ray(data, &ray, angle);
    dof = 0;
    while (dof < 15)
    {
        map_x = (int)ray.rx;
        map_y = (int)ray.ry;
        
        if (is_mob(data, map_x, map_y))
        {
            // Centre la porte sur Y ET ajuste X pour toucher le centre
            *ry = (float)map_y + 0.5f;
            // Recalcule rx pour qu'il corresponde au centre Y
            // rx = player.px + t * cos(angle), où t = (ry - player.py) / sin(angle)
            float t = (*ry - data->player.py) / sin(angle);
            *rx = data->player.px + t * cos(angle);
            return;
        }
        ray.rx += ray.xo;
        ray.ry += ray.yo;
        dof++;
    }
    *rx = ray.rx;
    *ry = ray.ry;
}
#endif 