/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:06:52 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/13 17:37:57 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd, int OP);
char	*ft_read(int fd, char *static_str);
char	*ft_line(char *statict_str);

void	*ft_calloc_gnl(size_t nmemb, size_t size);
int		ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(const char *s1, const char *s2);

char	*ft_strchr_gnl(const char *s, int c);
char	*ft_next(char *buffer);
char	*ft_free(char *buffer, char *buf);
char	*ft_clean(char *static_str);
char	*ft_strdup(const char *s);

#endif
