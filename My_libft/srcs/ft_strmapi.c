/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:07:29 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/13 11:40:58 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*new_str;

	index = 0;
	new_str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (s[index])
	{
		new_str[index] = f(index, s[index]);
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}

// char ft_to_upper(unsigned int i, char c)
// {
//     (void)i; 
//     if (c >= 'a' && c <= 'z')
//         return c - 32;
//     return c;
// }

// #include <stdio.h>

// int main(int argc, char **argv)
// {
//     if (argc < 2)
//         return 0;

//     for (int index = 1; index < argc; index++)
//     {
//         char *upper_str = ft_strmapi(argv[index], ft_to_upper);
//         if (upper_str)
//         {
//             printf("%s ", upper_str);
//             free(upper_str);
//         }
//     }
//     printf("\n");
//     return 0;
// }