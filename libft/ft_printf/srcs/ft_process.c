/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:46:49 by lsidan            #+#    #+#             */
/*   Updated: 2022/01/11 10:15:57 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_process(const char *format, size_t	*i, int	*ret, va_list args)
{
	int		_ret;

	_ret = *ret;
	ft_process_str(format, i, &_ret, args);
	ft_process_nbr(format, i, &_ret, args);
	ft_process_hexa(format, i, &_ret, args);
	*ret = _ret;
}

void	ft_process_str(const char *format, size_t *i, int	*ret, va_list args)
{
	int		_ret;
	char	*str;

	_ret = *ret;
	if (format[*i] == 's')
	{
		str = va_arg(args, char *);
		if (!str)
			str = "(null)";
		ft_putstr_fd(str, 1);
		_ret += ft_strlen(str);
	}
	else if (format[*i] == 'c')
	{
		ft_putchar_fd((char)va_arg(args, int), 1);
		_ret += 1;
	}
	else if (format[*i] == '%')
	{	
		ft_putchar_fd('%', 1);
		_ret += 1;
	}
	*ret = _ret;
}

void	ft_process_nbr(const char *format, size_t *i, int *ret, va_list args)
{
	long long			nb;
	unsigned long long	nb_u;
	size_t				k;
	int					_ret;

	k = *i;
	_ret = *ret;
	if (format[k] == 'i' || format[k] == 'd')
	{
		nb = va_arg(args, int);
		ft_putnbr((int) nb, 1, &_ret);
	}
	if (format[k] == 'u')
	{
		nb_u = va_arg(args, unsigned int);
		ft_putnbr_u_fd(nb_u, 1, &_ret);
	}
	*i = k;
	*ret = _ret;
}

void	ft_process_hexa(const char *format, size_t *i, int *ret, va_list args)
{
	int					_ret;
	unsigned long long	p;

	_ret = *ret;
	if (format[*i] == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", &_ret);
	else if (format[*i] == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", &_ret);
	else if (format[*i] == 'p')
	{
		ft_putstr_fd("0x", 1);
		p = va_arg(args, unsigned long);
		ft_putnbr_base(p, "0123456789abcdef", &_ret);
		_ret += 2;
	}
	*ret = _ret;
}
