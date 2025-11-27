/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:04:12 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 12:04:57 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

unsigned int	get_pixel_up(char *img, int *vars)
{
	int	offset;

	offset = vars[1] * vars[3] + vars[0] * (vars[2] / 8);
	return (*(unsigned int *)(img + offset));
}

void	put_pixel_up(char *img, int *vars)
{
	int	offset;

	offset = vars[1] * vars[4] + vars[0] * (vars[3] / 8);
	*(unsigned int *)(img + offset) = vars[5];
}

#endif