// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   render.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/21 11:55:39 by hrouchy           #+#    #+#             */
// /*   Updated: 2025/10/29 16:21:27 by hrouchy          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/cub3d.h"

// #define FOV (M_PI / 3)

// #ifdef BONUS

// #include <math.h>

// static void draw_wall_column(t_data *data, int x, int line_h,
//                              int line_off, int color)
// {
//     int y;
//     int draw_y;
//     int screen_h = 480;  // Ou mieux : défini comme constante globale
//     y = 0;
//     while (y < line_h)
//     {
//         draw_y = line_off + y;
//         if (draw_y >= 0 && draw_y < screen_h)  // Utilise la variable
//             put_pixel(data->win->img, x, draw_y, color);
//         y++;
//     }
// }
// // static void draw_wall_column(t_data *data, int x, int line_h,
// //     int line_off, int color)
// // {
// //     int screen_h = 480;
// //     int y_start = 0;      // Premier pixel du mur à dessiner
// //     int y_end = line_h;   // Dernier pixel du mur à dessiner
    
// //     // Si le mur commence au-dessus de l'écran
// //     if (line_off < 0)
// //         y_start = -line_off;  // Sauter les pixels hors écran
    
// //     // Si le mur finit en-dessous de l'écran
// //     if (line_off + line_h > screen_h)
// //         y_end = screen_h - line_off;  // Arrêter avant le bord
    
// //     // Dessiner uniquement la partie visible
// //     for (int y = y_start; y < y_end; y++)
// //     {
// //         int draw_y = line_off + y;
// //         if (draw_y >= 0 && draw_y < screen_h)
// //             put_pixel(data->win->img, x, draw_y, color);
// //     }
// // }
// static void process_single_ray(t_data *data, int i, float ra)
// {
//     float rx_h, ry_h, rx_v, ry_v;
//     float dist_h, dist_v, dist_final;
//     int line_h, line_off;
//     int face_index;
//     float rx_final, ry_final;
//     float plane_dist;
// 	int screen_h = 480;
// 	int screen_w = 640;
//     // Calcul des intersections horizontales et verticales
//     cast_horizontal_ray(data, &rx_h, &ry_h, ra);
//     cast_vertical_ray(data, &rx_v, &ry_v, ra);

//     // Calcul des distances
//     dist_h = sqrtf(powf(rx_h - data->player.px, 2) +
//                    powf(ry_h - data->player.py, 2));
//     dist_v = sqrtf(powf(rx_v - data->player.px, 2) +
//                    powf(ry_v - data->player.py, 2));

//     // Choisir le mur le plus proche
//     dist_final = fmin(dist_h, dist_v);
//     dist_final *= cos(data->player.pa - ra); // correction fisheye
//     if (dist_final < 0.1f)
//         dist_final = 0.1f;

//     // Calcul de la hauteur de mur avec projection plane
//     plane_dist = (screen_w / 2) / tan(data->fov / 2);
//     line_h = (int)(plane_dist / dist_final);

//     // if (line_h > screen_h)
//     //     line_h = screen_h;
//     line_off = (screen_h - line_h) / 2 + data->tilt;
// 	// printf("%d\n",line_off);
//     // Détermination de la face touchée et dessiner
//     if (dist_h < dist_v) // mur horizontal
//     {
//         face_index = (ra > M_PI) ? 0 : 2; // 0 = nord, 2 = sud
//         rx_final = rx_h;
//         ry_final = ry_h;
//         draw_wall_column(data,i,line_h,line_off, 0xFF0000);
//     }
//     else // mur vertical
//     {
//         face_index = (ra > M_PI && ra < 3 * M_PI) ? 3 : 1; // 3 = ouest, 1 = est
//         rx_final = rx_v;
//         ry_final = ry_v;
//         draw_wall_column(data,i,line_h,line_off, 0xA33333);
//     }
// }

// void	draw_walls_3d(t_data *data)
// {
// 	float	ra;
// 	int		i;

// 	if (!data || !data->map || !data->map->map)
// 	{
// 		printf("la y pas de map\n");
// 		return ;
// 	}
// 	// draw_background_mand(data);
// 	i = 0;
// 	while (i < 640)
// 	{
// 		ra = data->player.pa - (data->fov / 2) + (FOV * i) / 640;
// 		while (ra < 0)
// 			ra += 2 * M_PI;
// 		while (ra >= 2 * M_PI)
// 			ra -= 2 * M_PI;
// 		process_single_ray(data, i, ra);
// 		i++;
// 	}
// }
// #endif
