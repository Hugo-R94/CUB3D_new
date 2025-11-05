/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:33:47 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/13 11:01:56 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	int start = 7;
// 	size_t len = 10;
// 	char *str = "lorem ipsum dolor sit amet";
// 	char *strsub = ft_substr(str,start,len);
// 	if (!(strsub = ft_substr(str, start, len)))
// 		printf("NULL");
// 	else
// 		printf("%s",strsub);
// 	if (str == strsub)
// 		printf("\nA new string was not returned");
// }

// int	main(void)
// {
// 	char const	*s = "lorem ipsum dolor sit amet";
// 	unsigned int	start = 7;
// 	size_t	len = 10;

// 	printf("start index: %d\nsubstring length: %zu\n", start, len );
// 	printf("string: %s\nft_substr: %s\n", s, ft_substr(s, start, len));
// 	//printf("string: %s\nsubstr: %d\n", s, substr(s, start, len));
// }

// int main()
// {
// 	printf("%s",ft_substr("hello", 2, 10));
// }