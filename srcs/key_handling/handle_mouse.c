/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:25:16 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/07 12:13:11 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS

int	handle_mouse_click(int button, int x, int y, t_data *data)
{
	int			i;
	float		scale[2];
	int			mouse_scaled[2];
	t_button	*b;
	data->mouse.mouse_pressed = 1;
	if (button != 1)
		return (0);
	scale[0] = 640.0f / (float)data->res_x;
	scale[1] = 480.0f / (float)data->res_y;
	mouse_scaled[0] = (int)(x * scale[0]);
	mouse_scaled[1] = (int)(y * scale[1]);
	i = -1;
	while (data->current_buttons[++i].on_click)
	{
		b = &data->current_buttons[i];
		if (mouse_scaled[0] >= b->x && mouse_scaled[0] <= b->x + b->width
			&& mouse_scaled[1] >= b->y && mouse_scaled[1] <= b->y + b->height)
		{
			if (b->on_click)
				b->on_click(data);
			break ;
		}
	}
	return (0);
}

int handle_mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 1) // bouton gauche
		data->mouse.mouse_pressed = 1;
	if (data->mouse.mouse_pressed == 1)
		printf("mouse preessed\n");
	data->mouse.mouse_x = x;
	data->mouse.mouse_y = y;
	return (0);
}

int handle_mouse_release(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->mouse.mouse_pressed = 0;
	data->mouse.mouse_x = x;
	data->mouse.mouse_y = y;
	return (0);
}
/*
 * update_mouse_pos_menu :
 *   - convertit la position écran -> coordonnées UI (640x480 base)
 *   - calcule le delta depuis old_mouse_* puis met à jour old_mouse_*
 */
void update_mouse_pos_menu(t_data *data, int x, int y)
{
	float scale[2];
	int mouse_scaled_x;
	int mouse_scaled_y;

	scale[0] = 640.0f / (float)data->res_x;
	scale[1] = 480.0f / (float)data->res_y;
	mouse_scaled_x = (int)(x * scale[0]);
	mouse_scaled_y = (int)(y * scale[1]);

	/* calcule delta (mouvement) par rapport à la dernière position */
	data->mouse.x_accel = mouse_scaled_x - data->mouse.old_mouse_x;
	data->mouse.y_accel = mouse_scaled_y - data->mouse.old_mouse_y;

	/* met à jour positions */
	data->mouse.mouse_x = mouse_scaled_x;
	data->mouse.mouse_y = mouse_scaled_y;

	/* on stocke la dernière position pour le prochain delta */
	data->mouse.old_mouse_x = mouse_scaled_x;
	data->mouse.old_mouse_y = mouse_scaled_y;
}

/*
 * update_mouse_pos_game :
 *   - utilise le centre de la fenêtre comme "origine" => relative mouse mode
 *   - applique delta_x à la rotation du joueur (sensitivity ajustable)
 *   - recentre la souris au centre de la fenêtre si la fenêtre existe
 *   - met mouse_x/mouse_y à la position centrale pour que le système de hover ne
 *     pense pas que la souris est ailleurs (utile si tu retombes en menu)
 */
void update_mouse_pos_game(t_data *data, int x, int y)
{
	int center_x;
	int center_y;
	int delta_x;
	int delta_y;
	float sensitivity = 0.0001f;
	/* proteger contre data null */
	if (!data || !data->win)
		return ;

	center_x = data->res_x / 2;
	center_y = data->res_y / 2;

	delta_x = x - center_x;
	delta_y = y - center_y;

	/* appliquer rotation */
	data->player.pa += delta_x * data->mouse.sensitivity / 1.5;
	data->player.parralax_x += (delta_x * data->mouse.sensitivity) * (18.0f * M_PI);
	if (data->player.pa < 0)
		data->player.pa += 2.0f * M_PI;
	else if (data->player.pa >= 2.0f * M_PI)
		data->player.pa -= 2.0f * M_PI;

	/* update tilt (regard vertical) si tu veux */
	data->tilt -= (delta_y * (data->mouse.sensitivity * 350));
	// data->tilt -= (delta_y / 2);//hein
	if (data->tilt > 200)
		data->tilt = 200;	
	if (data->tilt < -200)
		data->tilt = -200;
	/* stocker delta pour debug / usage */
	data->mouse.x_accel = delta_x;
	data->mouse.y_accel = delta_y;

	/* pour que la logique de hover en menu reste cohérente,
	 * on place la position "logique" de la souris au centre */
	data->mouse.mouse_x = center_x;
	data->mouse.mouse_y = center_y;
	data->mouse.old_mouse_x = center_x;
	data->mouse.old_mouse_y = center_y;

	/* recentrer la souris physiquement si la fenêtre est valide */
	if (data->win->win && data->win->mlx)
		mlx_mouse_move(data->win->mlx, data->win->win, center_x, center_y);
}

/*
 * handle_mouse_move :
 *   - route vers mode jeu ou menu
 *   - calcule quel bouton est hover
 */
int	handle_mouse_move(int x, int y, t_data *data)
{
	int			i;
	t_button	*b;

	if (!data)
		return (0);

	if (data->current_pg == GAME_PG)
		update_mouse_pos_game(data, x, y);
	else
		update_mouse_pos_menu(data, x, y);

	data->mouse.button_hovered = -1;
	i = -1;
	while (data->current_buttons[++i].on_click)
	{
		b = &data->current_buttons[i];
		if (data->mouse.mouse_x >= b->x && data->mouse.mouse_x <= b->x + b->width
			&& data->mouse.mouse_y >= b->y && data->mouse.mouse_y <= b->y + b->height)
		{
			data->mouse.button_hovered = i;
			break ;
		}
	}

	/* debug utile — commente si c'est trop verbeux */
	// printf("mouse x = %d | mouse y = %d\n", data->mouse.mouse_x, data->mouse.mouse_y);
	// printf("accel x = %d | accel y = %d\n", data->mouse.x_accel, data->mouse.y_accel);

	return (0);
}

#endif
