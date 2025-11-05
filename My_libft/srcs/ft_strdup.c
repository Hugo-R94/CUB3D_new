/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:35:39 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/07 10:59:07 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	int		size_source;
	int		i;
	char	*str_dup;

	size_source = ft_strlen(source);
	i = 0;
	str_dup = (char *)malloc((size_source * sizeof(char)) + 1);
	if (!str_dup)
		return (NULL);
	while (i < size_source)
	{
		str_dup[i] = source[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// char	*ft_strdup(const char *source); // ta fonction

// int	main(void)
// {
// 	char *s;
// 	char *copy;

// 	s = "Hello, World!";
// 	copy = ft_strdup(s);
// 	printf("Original : %s\n", s);
// 	printf("Duplicate: %s\n", copy);
// 	free(copy);

// 	s = "";
// 	copy = ft_strdup(s);
// 	printf("Empty: %s\n", copy);
// 	free(copy);

// 	// Ne surtout pas faire : s = NULL; ft_strdup(s); -> undefined behavior
// 	return (0);
// }

// int main()
// {
// 	char *str ="lorem ipsum dolor sit amet";
// 	char *str_dup = ft_strdup(str);
// 	char *str_duporiginal = strdup(str);
// 	printf("mine = %s\n",str_dup);
// 	printf("reel = %s\n",str_duporiginal);
// 	if (!(str_dup = ft_strdup(str)))
// 		printf("NULL");
// 	else
// 		printf("%s",str_dup);
// 	if (str_dup == str)
// 		printf("\nstr_dup's adress == str's adress");	
// }

// int	main(void)
// {
// 	int		i;
// 	char	*src;
// 	char	*dup;

// 	i = 0;
// 	src = "sans que ni tete mais qui mets quand meme bien";
// 	dup = ft_strdup(src);
// 	while (dup[i])
// 	{
// 		printf("%c", dup[i]);
// 		i++;
// 	}
// 	free(dup);
// 	dup = 0;
// 	return (0);
// }