/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:31:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/02 11:31:59 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	index;

	index = 0;
	if (c == '\0' && s[0] == '\0')
		return ((char *)&s[0]);
	while (s[index])
	{
		if ((unsigned char)s[index] == (unsigned char)c)
			return ((char *)&s[index]);
		index++;
	}
	if ((unsigned char)s[index] == (unsigned char)c)
		return ((char *)&s[index]);
	return (NULL);
}

// int main(void)
// {
//     char base_str[] = "";
//     char to_find = '\0';
//     printf("strchr    = %p\n",strchr(base_str,to_find));
//     printf("ft_strchr = %p",ft_strchr(base_str,to_find));
// }