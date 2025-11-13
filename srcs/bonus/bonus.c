/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:47:25 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/13 14:32:29 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS
void    init_mob(t_data *data)
{
   int mob_count;
   int y;
   int x;
   int i;


   if (data->mob)
       free(data->mob);
   mob_count = 0;
   y = 0;
   while (data->map->map[y])
   {
       x = 0;
       while (data->map->map[y][x])
       {
           if (data->map->map[y][x] == 'M')
               mob_count++;
           x++;
       }
       y++;
   }
   data->mob = calloc(mob_count, sizeof(t_mob));
   y = 0;
   i = 0;
   while (data->map->map[y])
   {
       x = 0;
       while (data->map->map[y][x])
       {
           if (data->map->map[y][x] == 'M')
           {
               data->mob[i].mx = (float)x;
               data->mob[i].my = (float)y;
               data->mob[i].hp = 2;
               data->mob[i].is_alive = 1;
               data->mob[i].id = i;
               data->mob[i].chase = 0;
               i++;
           }
           x++;
       }
       y++;
   }
   data->mob_count = i;
   i = 0;
   while (i < mob_count)
   {
       printf("mob n%d mx = %f | my = %f | hp = %d\n",i, data->mob[i].mx,data->mob[i].my,data->mob[i].hp);
       i++;
   }
  
}

void	new_map_random(t_data *data)
{
	int	len;

	if (data->map)
		free_map(data->map->map);
	data->map->map = make_map(data);
	printf("debut\n");
	data->map->height = 0;
	data->map->width = 0;
	while (data->map->map[data->map->height])
	{
		len = ft_strlen(data->map->map[data->map->height]);
		if (len > data->map->width)
			data->map->width = len;
		data->map->height++;
	}
	get_player_original_pos(data);
	print_map(data->map->map);
	init_mob(data);
	printf("fin\n");
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	// printf("px = %f | py = %f\n", data->player.px, data->player.py);
	mlx_game_loop(data);
	return (0);
}

#endif