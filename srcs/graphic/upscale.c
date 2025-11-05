/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:52:17 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/04 12:34:38 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS

static unsigned int get_pixel_up(char *img, int *vars)
{
    int offset;

    offset = vars[1] * vars[3] + vars[0] * (vars[2] / 8);
    return (*(unsigned int *)(img + offset));
}

static void put_pixel_up(char *img, int *vars)
{
    int offset;

    offset = vars[1] * vars[4] + vars[0] * (vars[3] / 8);
    *(unsigned int *)(img + offset) = vars[5];
}

static void scale_pixel(char *dst, int *scale_v, int *dst_v)
{
    int dx;
    int dy;
    int tmp[6];

    dy = -1;
    while (++dy < scale_v[2])
    {
        dx = -1;
        while (++dx < scale_v[2])
        {
            tmp[0] = scale_v[0] * scale_v[2] + dx;
            tmp[1] = scale_v[1] * scale_v[2] + dy;
            tmp[3] = dst_v[0];
            tmp[4] = dst_v[1];
            tmp[5] = scale_v[3];
            put_pixel_up(dst, tmp);
        }
    }
}

static void upscale_loop(char *src, char *dst, int *p)
{
    int y;
    int x;
    int scale_v[4];
    int src_v[4];

    y = -1;
    while (++y < 480)
    {
        x = -1;
        while (++x < 640)
        {
            src_v[0] = x;
            src_v[1] = y;
            src_v[2] = p[1];
            src_v[3] = p[2];
            scale_v[3] = get_pixel_up(src, src_v);
            scale_v[0] = x;
            scale_v[1] = y;
            scale_v[2] = p[0];
            scale_pixel(dst, scale_v, &p[3]);
        }
    }
}

void    upscale_to(t_data *data, int target_w, int target_h)
{
    int     p[5];
    void    *new_img;
    char    *src_data;
    char    *dst_data;
    int     endian;

    p[0] = target_w / 640;
    if (p[0] <= 0 || p[0] != target_h / 480)
        return ;
    src_data = mlx_get_data_addr(data->win->img, &p[1], &p[2], &endian);
    new_img = mlx_new_image(data->win->mlx, target_w, target_h);
    dst_data = mlx_get_data_addr(new_img, &p[3], &p[4], &endian);
    upscale_loop(src_data, dst_data, p);
    mlx_destroy_image(data->win->mlx, data->win->img);
    data->win->img = new_img;
}

void	upscale(t_data *data)
{
	int	w = data->res_x;
	int	h = data->res_y;

	if (w <= 640 && h <= 480)
		return;
	while (1)
	{
		if (w >= 1920 && h >= 1440)
		{
			upscale_to(data, 1920, 1440);
			break;
		}
		else if (w >= 1280 && h >= 960)
		{
			upscale_to(data, 1280, 960);
			break;
		}
		else if (w >= 640 && h >= 480)
		{
			upscale_to(data, 640, 480);
			break;
		}
		else
			break;
	}
}

#endif