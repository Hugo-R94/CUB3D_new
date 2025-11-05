/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:37:00 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/13 11:05:57 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isinset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		index;
	int		index2;
	int		index3;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	index = 0;
	while (s1[index] && ft_isinset(s1[index], set))
		index++;
	index2 = 0;
	while (s1[index2])
		index2++;
	index2--;
	while (index2 >= index && ft_isinset(s1[index2], set))
		index2--;
	trimmed = malloc(index2 - index + 2);
	if (!trimmed)
		return (NULL);
	index3 = 0;
	while (index <= index2)
		trimmed[index3++] = s1[index++];
	trimmed[index3] = '\0';
	return (trimmed);
}

// #include <stdio.h>

// int		main(void)
// {
// 	char 	*charset = " \n\t\v\f ";
// 	char 	*s1 = "\t \n\n \t\t \n\n\nHello \t  Please\n \t\n";
// 	printf("%s\n", ft_strtrim(s1,charset));
// 	return (0);
// }	