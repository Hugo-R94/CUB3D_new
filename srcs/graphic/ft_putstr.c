/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:09:05 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 12:18:23 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
/* --- Copie d'une lettre sur l'image principale --- */
void	cop_l_to_img(t_img *src, t_img *dst, int pos[2], uint32_t p_col)
{
	int			x;
	int			y;
	uint32_t	color;
	int			dst_x;
	int			dst_y;

	y = -1;
	while (++y < src->height)
	{
		x = -1;
		while (++x < src->width)
		{
			color = get_pixel(src, x, y);
			dst_x = pos[0] + x;
			dst_y = pos[1] + y;
			if (dst_x < 0 || dst_y < 0 || dst_x >= dst->width
				|| dst_y >= dst->height)
				continue ;
			if (color == 0x00000)
				put_pixel(dst, dst_x, dst_y, p_col);
		}
	}
}

/* --- Dessine une lettre (depuis ton dossier alphabet) --- */
void	draw_letter(t_data *data, char *str, int pos[2], uint32_t print_colour)
{
	char	txt_name[32];
	t_txt	*txt;

	if (!data || !data->win || !data->win->img || !data->txt)
	{
		printf("Erreur : draw_letter() paramètres invalides\n");
		return ;
	}
	txt = find_texture(data->txt, str);
	if (!txt)
	{
		printf("Erreur : texture '%s' introuvable\n", txt_name);
		return ;
	}
	if (!txt->img.data)
	{
		printf("Erreur : texture '%s' non initialisée\n", txt_name);
		return ;
	}
	cop_l_to_img(&txt->img, data->win->img, pos, print_colour);
}

static void	put_single_char(t_data *data, char c,
	int pos[2], uint32_t color)
{
	char	letter[2];
	int		letter_pos[2];

	letter[0] = c;
	letter[1] = '\0';
	letter_pos[0] = pos[0];
	letter_pos[1] = pos[1];
	draw_letter(data, letter, letter_pos, color);
}

void	put_string_to_img(t_data *data, int pos[2],
	uint32_t color, char *str)
{
	int	i;
	int	x;
	int	y;

	if (!data || !str)
		return ;
	x = pos[0];
	y = pos[1];
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			put_single_char(data, str[i], (int []){x, y}, color);
		x += 25;
		i++;
	}
}

#endif