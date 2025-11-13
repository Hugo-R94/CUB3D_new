/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:46:03 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/06 16:15:44 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	get_pixel(t_img *img, int x, int y)
{
	int	offset;

	if (!img || !img->data)
	{
		
		return (0x000000);
	}
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0x000000);
	offset = y * img->size_line + x * (img->bpp / 8);
	return (*(unsigned int *)(img->data + offset));
}

void	put_pixel(t_img *img, int x, int y, uint32_t color)
{
	int	offset;

	if (!img || !img->data || x < 0 || y < 0)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	offset = y * img->size_line + x * (img->bpp / 8);
	*(unsigned int *)(img->data + offset) = color;
}

void	get_img_size(char **element, int size[2])
{
	int	i;
	int	width;
	int	len;

	i = 0;
	width = 0;
	if (!element)
	{
		size[0] = 0;
		size[1] = 0;
		return ;
	}
	while (element[i])
	{
		len = 0;
		while (element[i][len])
			len++;
		if (len > width)
			width = len;
		i++;
	}
	size[0] = width;
	size[1] = i;
}

#ifdef BONUS

//PLUS DE 4 ARGS MAIS FONCTION UTILITAIRE A COMMENTER
void	draw_rect(t_data *data, int pos[2], int scale[2], int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < scale[0])
	{
		put_pixel(data->win->img, pos[0] + i, pos[1], color);
		i++;
	}
	i = 0;
	while (i < scale[0])
	{
		put_pixel(data->win->img, pos[0] + i, pos[1] + scale[1] - 1, color);
		i++;
	}
	j = 0;
	while (j < scale[1])
	{
		put_pixel(data->win->img, pos[0], pos[1] + j, color);
		put_pixel(data->win->img, pos[0] + scale[0] - 1, pos[1] + j, color);
		j++;
	}
}
void	draw_rect_fill(t_data *data, int pos[2], int scale[2], int color)
{
	int	i;
	int	j;

	j = 0;
	while(j < scale[1])
	{
		i = 0;
		while (i < scale[0])
		{
			put_pixel(data->win->img, pos[0] + i, pos[1] + j, color);
			i++;
		}
		j++;
	}
}
#endif