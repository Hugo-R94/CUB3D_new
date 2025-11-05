/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:26:03 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/14 11:22:36 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(const char *s, ...);
int		ft_putformat(char *str);
int		ft_putchar(unsigned int c);
int		ft_count_format(char *s);
int		ft_is_format(char c);
int		ft_putstr(char *str);
int		ft_putnb(int nb);
int		ft_idformat(va_list args, char *str, int index);
int		ft_puthexa(unsigned long int nb, bool up);
int		ft_putptr(void *ptr);
int		ft_putunsigned(int nb);

#endif
