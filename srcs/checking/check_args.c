/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:11:13 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/24 16:33:46 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	validate_args(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("%scub3D should take 1 argument, no more, no less%s\n",
			RED, RESET);
		exit(1);
	}
	if (name_checker(av[1]) == 0)
	{
		ft_printf("Error: ");
		ft_printf("Invalid map name: %s%s%s > Map must be a .cub file.\n",
			RED, av[1], RESET);
		exit(1);
	}
}

static void	check_file_access(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		printf("Error: %s%s%s does not exist.\n", RED, filename, RESET);
		exit(1);
	}
	if (access(filename, R_OK) != 0)
	{
		printf("Error: %s%s%s Permission denied.\n", RED, filename, RESET);
		exit(1);
	}
	if (access(filename, X_OK) == 0)
	{
		printf("Error: %s%s%s seems to be a directory or executable.\n",
			RED, filename, RESET);
		exit(1);
	}
}

int	check_arg_and_open(int ac, char **av)
{
	validate_args(ac, av);
	check_file_access(av[1]);
	return (open(av[1], O_RDONLY));
}
