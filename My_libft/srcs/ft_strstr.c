/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:36:46 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/02 12:03:53 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *src, char *str)
{
	int	index_src;
	int	index_to_find;

	index_src = 0;
	if (str[0] == '\0')
		return (src);
	while (src[index_src])
	{
		index_to_find = 0;
		if (src[index_src] == str[index_to_find])
		{
			while (str[index_to_find]
				&& src[index_src + index_to_find] == str[index_to_find])
			{
				if (str[index_to_find + 1] == '\0')
					return (&src[index_src]);
				index_to_find++;
			}
		}
		index_src++;
	}
	return (NULL);
}

// int main()
// {
// 	char *str_src1 = "les chaussettes sale de la reine";
// 	char *str_to_find1 = " ";
// 	printf("ft_strstr trouve a = %p \n", ft_strstr(str_src1, str_to_find1));
// 	printf("strstr trouve a    = %p \n", strstr(str_src1, str_to_find1));

// 	printf("\n");

// 	char *str_src2 = "hello world";
// 	char *str_to_find2 = "world";
// 	printf("ft_strstr trouve a = %p \n", ft_strstr(str_src2, str_to_find2));
// 	printf("strstr trouve a    = %p \n", strstr(str_src2, str_to_find2));

// 	printf("\n");

// 	char *str_src3 = "abcdef";
// 	char *str_to_find3 = "gh";
// 	printf("ft_strstr trouve a = %p \n", ft_strstr(str_src3, str_to_find3));
// 	printf("strstr trouve a    = %p \n", strstr(str_src3, str_to_find3));

// 	printf("\n");

// 	char *str_src4 = "test";
// 	char *str_to_find4 = "";
// 	printf("ft_strstr trouve a = %p \n", ft_strstr(str_src4, str_to_find4));
// 	printf("strstr trouve a    = %p \n", strstr(str_src4, str_to_find4));

// 	printf("\n");

// 	char *str_src5 = "";
// 	char *str_to_find5 = "test";
// 	printf("ft_strstr trouve a = %p \n", ft_strstr(str_src5, str_to_find5));
// 	printf("strstr trouve a    = %p \n", strstr(str_src5, str_to_find5));

// 	return 0;
// }