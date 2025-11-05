/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:30:52 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/07 10:59:12 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		index;
	char	*buffer;

	buffer = NULL;
	index = 0;
	if (c == '\0' && s[0] == '\0')
		return ((char *)&s[0]);
	while (s[index])
	{
		if ((unsigned char)s[index] == (unsigned char)c)
			buffer = (char *)&s[index];
		index++;
	}
	if ((unsigned char)s[index] == (unsigned char)c)
		buffer = (char *)&s[index];
	if (buffer == NULL)
		return (NULL);
	else
		return (buffer);
}

// int main(void)
// {
//     char base_str[] = "tripouille";
//     char to_find = (char)('t'+256);
//     printf("strrchr    = %p\n",strrchr(base_str,to_find));
//     printf("ft_strrchr = %p",ft_strrchr(base_str,to_find));
// }