/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:53:17 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/13 17:38:25 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd, int OP)
{
	static char	*static_str;
	char		*line;

	if (OP == 1)
	{
		free(static_str);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) == -1)
	{
		if (static_str)
		{
			free(static_str);
			static_str = NULL;
		}
		return (NULL);
	}
	static_str = ft_read(fd, static_str);
	if (!static_str)
		return (NULL);
	line = ft_line(static_str);
	static_str = ft_clean(static_str);
	return (line);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	char	*str;
	size_t	index;

	index = 0;
	if (nmemb != 0 && size != 0 && (nmemb * size) / nmemb != size)
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	while (index < nmemb * size)
		str[index++] = '\0';
	return (str);
}

char	*ft_read(int fd, char *static_str)
{
	char	*buffer;
	int		nbytes;

	if (!static_str)
		static_str = ft_calloc_gnl(BUFFER_SIZE, 1);
	buffer = ft_calloc_gnl((BUFFER_SIZE + 2), sizeof(char));
	if (!buffer)
		return (NULL);
	nbytes = 1;
	while (nbytes > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(buffer);
			free(static_str);
			static_str = NULL;
			return (NULL);
		}
		buffer[nbytes] = '\0';
		static_str = ft_free(static_str, buffer);
	}
	free(buffer);
	return (static_str);
}

char	*ft_line(char *statict_str)
{
	char	*line;
	int		index;

	index = 0;
	if (!statict_str[index])
		return (NULL);
	while (statict_str[index] && statict_str[index] != '\n')
		index++;
	line = ft_calloc_gnl((index + 2), sizeof(char));
	if (!line)
		return (NULL);
	index = 0;
	while (statict_str[index] && statict_str[index] != '\n')
	{
		line[index] = statict_str[index];
		index++;
	}
	if (statict_str[index] && statict_str[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

char	*ft_clean(char *static_str)
{
	int		i;
	int		j;
	char	*new_static;

	i = 0;
	j = 0;
	while (static_str[i] && static_str[i] != '\n')
		i++;
	if (!static_str[i])
	{
		free(static_str);
		return (NULL);
	}
	new_static = ft_calloc_gnl((ft_strlen_gnl(static_str) - i), sizeof(char));
	if (!new_static)
		return (NULL);
	i++;
	while (static_str[i])
		new_static[j++] = static_str[i++];
	new_static[j] = '\0';
	free(static_str);
	return (new_static);
}
