/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:32:56 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/13 11:21:07 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	nb_digits(int n)
{
	int			digits;
	long int	nb;

	nb = n;
	digits = 1;
	if (n < 0)
	{
		digits++;
		nb = -nb;
	}
	else
		nb = n;
	while (nb >= 10)
	{
		nb = nb / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nb;

	len = nb_digits(n);
	str = malloc(len + 1);
	nb = n;
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int i = 0;
// 	int tab[5] = {-2147483648, -42, 0, 42, 2147483647};

// 	while (i < 5)
// 		printf("%s\n", ft_itoa(tab[i++]));

// 	return 0;
// }

// int	main(void)
// {
// 	int i = -2147483648;

// 	while (i < 2147483647)
// 	{
// 		printf("%s\n", ft_itoa(i));
// 		i++;
// 	}
// 	return 0;
// }