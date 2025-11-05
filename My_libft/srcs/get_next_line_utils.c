/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:53:35 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/13 17:37:19 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;	

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strcat_gnl(char *dest, const char *src)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	if (!dest || !src)
	{
		return (NULL);
	}
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[e] != '\0')
	{
		dest[i] = src[e];
		e++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str_join;

	if (!s1 || !s2)
		return (NULL);
	str_join = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2)+1);
	if (!str_join)
		return (NULL);
	str_join[0] = '\0';
	ft_strcat_gnl(str_join, s1);
	ft_strcat_gnl(str_join, s2);
	return (str_join);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	index;

	if (!s)
		return (NULL);
	index = 0;
	while (s[index])
	{
		if (s[index] == c)
			return ((char *)&s[index]);
		index++;
	}
	return (NULL);
}

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin_gnl(buffer, buf);
	free(buffer);
	return (temp);
}
