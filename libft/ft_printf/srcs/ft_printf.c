/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:53:02 by lsidan            #+#    #+#             */
/*   Updated: 2021/11/23 09:48:28 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//puxX%

#include "../include/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;
	size_t	i;

	i = -1;
	ret = 0;
	va_start(args, format);
	if (ft_check_format(format))
	{
		ft_putstr_fd(format, 1);
		return (ft_strlen(format));
	}
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i += 1;
			ft_process(format, &i, &ret, args);
		}
		else
			ret += write(1, &format[i], 1);
	}
	va_end(args);
	return (ret);
}

BOOL	ft_check_format(const	char	*str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '%' && (str[i + 1] == 'c' || \
		str[i + 1] == 's' || str[i + 1] == 'p' || str[i + 1] == 'd' \
		|| str[i + 1] == 'i' || str[i + 1] == 'u' || str[i + 1] == 'x' \
		|| str[i + 1] == 'X' || str[i + 1] == '%'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
