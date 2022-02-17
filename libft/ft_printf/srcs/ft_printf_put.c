/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:26:23 by lsidan            #+#    #+#             */
/*   Updated: 2022/01/11 10:20:18 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putnbr_base(unsigned long long nbr, char *base, int	*ret)
{
	int				_ret;
	unsigned long	nb;

	_ret = *ret;
	nb = nbr;
	if (nb < 0)
		nb *= -1;
	if (nb >= 16)
		ft_putnbr_base(nb / 16, base, &_ret);
	ft_putchar_fd(base[nb % 16], 1);
	_ret++;
	*ret = _ret;
	return (_ret);
}

int	ft_putnbr_u_fd(unsigned int nb, int fd, int *ret)
{
	unsigned int	nb1;
	int				_ret;

	_ret = *ret;
	nb1 = nb;
	if (nb1 >= 10)
	{
		ft_putnbr_u_fd((nb1 / 10), fd, &_ret);
		ft_putnbr_u_fd((nb1 % 10), fd, &_ret);
	}
	else
	{
		ft_putchar_fd(nb1 + 48, fd);
		_ret++;
	}
	*ret = _ret;
	return (_ret);
}

int	ft_putnbr(int nb, int fd, int *ret)
{
	long long	nb1;
	int			_ret;

	nb1 = nb;
	_ret = *ret;
	if (nb1 < 0)
	{
		ft_putchar_fd('-', fd);
		nb1 *= -1;
		_ret++;
	}
	if (nb1 >= 10)
	{
		ft_putnbr((nb1 / 10), fd, &_ret);
		ft_putnbr((nb1 % 10), fd, &_ret);
	}
	else
	{
		ft_putchar_fd(nb1 + 48, fd);
		_ret++;
	}
	*ret = _ret;
	return (_ret);
}
