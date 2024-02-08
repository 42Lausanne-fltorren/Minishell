/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:07:26 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 17:20:06 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		width;
	int		dot;
	int		precision;
	int		plus;
	int		space;
	int		alt;
}				t_flags;

int		ft_put_type(va_list args, const char *format, int i, t_flags flags);
int		ft_get_flags(va_list args, const char *format, int i, t_flags *flags);

int		ft_put_char(va_list args, t_flags flags);
int		ft_put_str(va_list args, t_flags flags);
int		ft_put_int(va_list args, t_flags flags);
int		ft_put_uint(va_list args, t_flags flags);
int		ft_put_hex(va_list args, char type, t_flags flags);
int		ft_put_ptr(va_list args, t_flags flags);
int		ft_put_perc(t_flags flags);

char	*ft_strtoupper(char *str);
void	ft_put_width(int width, int len);
void	ft_put_zeroes(int width, int len);

void	ft_reassign(char **str, char *new);
char	*ft_join_spaces(char *str, int n);
char	*ft_join_zeroes(char *str, int n);
int		ft_get_precision(va_list args, const char *format,
			int i, t_flags *flags);
#endif