/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:57:18 by lsidan            #+#    #+#             */
/*   Updated: 2022/01/11 10:15:03 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BOOL unsigned int
# define TRUE 1
# define FALSE 0
# define EXIT_FAIL 0

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "../../libft.h"

int		ft_printf(const char *format, ...);
BOOL	ft_check_format(const	char	*str);
void	ft_process(const char *format, size_t	*i, int	*ret, va_list args);
void	ft_process_str(const char *format, size_t *i, int	*ret, va_list args);
void	ft_process_nbr(const char *format, size_t *i, int	*ret, va_list args);
void	ft_process_hexa(const char *format, size_t *i, int *ret, va_list args);
int		ft_putnbr_base(unsigned long long nbr, char *base, int *ret);
int		ft_putnbr_u_fd(unsigned int nb, int fd, int *ret);
int		ft_putnbr(int nb, int fd, int *ret);

#endif