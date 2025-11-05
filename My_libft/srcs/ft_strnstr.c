/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:36:28 by hrouchy           #+#    #+#             */
/*   Updated: 2025/04/28 10:36:28 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	index1;
	int	index2;

	index1 = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[index1] && (size_t)index1 < len)
	{
		index2 = 0;
		if (big[index1] == little[index2])
		{
			while (big[index1 + index2] == little[index2]
				&& (size_t)index1 + (size_t)index2 < len)
			{
				if (little[index2 + 1] == '\0')
					return ((char *)&big[index1]);
				index2++;
			}
			index2++;
		}
		index1++;
	}
	return (0);
}

// int main(int argc, char const *argv[])
// {
// 	char longstr[] = "les chaussettes de l'archiduchesse sont elles sechent ?";
// 	char shortstr[] = "e";
// 	printf("strnstr = %s", ft_strnstr(longstr,shortstr,4));
// 	printf("\n");
// 	return 0;
// }
