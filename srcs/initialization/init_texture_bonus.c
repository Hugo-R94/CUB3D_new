/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:51:39 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/19 18:56:04 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <string.h>
#ifdef BONUS
const char *texture_names[] = 
{
	"HUD_placeholder",
	// "mettre_nom_txt_ici",
	"Home_bg",
	"Home_ash",
	"Home_title",
	"HUD",
	"black",
	"wall_wood",
	"slider_base",
	"bos",
	"slider_button",
	"wall",
	"button",
	"shot",
	"button_200x125",
	"Ash_100",
	"Ash_75",
	"hand_right",
	"hand_left",
	"skull",
	"cloud_1",
	"Ash_50",
	"Ash_25",
	"test",
	"cloud",
	"door",
	"wall_re",
	"door_close",
	"gamemode_endless",
	"ground",
	"mob",
	"gamemode_survivor",
	"aim",
	"gamemode_mandatory",
	"gamemode_mainmenu",
	"necronomicon",
	"pointeur",
	"skybox",
	"floor",
	// Lettres majuscules
	"A", 
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",     
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",       
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	// Chiffres
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	NULL
};

t_txt	*init_paths(void)
{
	int		i;
	int		j;
	int		k;
	t_txt	*textures;

	i = 0;
	while (texture_names[i])
		i++;
	textures = ft_calloc(i + 1, sizeof(t_txt));
	if (!textures)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		textures[j].name = ft_strdup(texture_names[j]);
		if (!textures[j].name)
		{
			k = -1;
			while (++k < j)
			{
				free(textures[k].name);
				free(textures[k].path);
			}
			free(textures);
			return (NULL);
		}
		textures[j].path = ft_sprintf("txt/%s.xpm", textures[j].name);
		if (!textures[j].path)
		{
			k = -1;
			while (++k <= j)
				free(textures[k].name);
			free(textures);
			return (NULL);
		}
	}
	textures[i].name = NULL;
	textures[i].path = NULL;
	return (textures);
}

t_txt	*init_textures(t_data *data)
{
	t_txt	*textures;
	int		i;
	int		k;

	if (!data || !data->win || !data->win->mlx)
	{
		fprintf(stderr, "Erreur: MLX non initialisé!\n");
		return (NULL);
	}
	textures = init_paths();
	if (!textures)
		return (NULL);
	i = 0;
	while (textures[i].name)
	{
		printf("%stxt name = %s | txt path = %s\n%s",
			GRN, textures[i].name, textures[i].path, RESET);
		textures[i].img.image = mlx_xpm_file_to_image(
				data->win->mlx,
				textures[i].path,
				&textures[i].img.width,
				&textures[i].img.height
				);
		if (!textures[i].img.image)
		{
			fprintf(stderr, "Erreur: impossible de charger %s\n",
				textures[i].path);
			k = -1;
			while (textures[++k].name)
			{
				free(textures[k].name);
				free(textures[k].path);
			}
			free(textures);
			return (NULL);
		}
		textures[i].img.data = mlx_get_data_addr(
				textures[i].img.image,
				&textures[i].img.bpp,
				&textures[i].img.size_line,
				&textures[i].img.format
				);
		i++;
	}
	return (textures);
}

void	print_texture_set(t_txt *txt)
{
	int	i;

	i = 0;
	while (txt[i].name)
	{
		printf("texture[%i].name = %s | texture[%i].path = %s\n",
			i, txt[i].name, i, txt[i].path);
		i++;
	}
}
#endif