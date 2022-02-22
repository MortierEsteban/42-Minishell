/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:32:21 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/18 17:34:52 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	echo(char *str, int fd, int flag)
{
	if (!str || fd < 0 || fd > 99998)
		return (1);
	if (flag)
	{
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else
		ft_putstr_fd(str, fd);
	return (0);
}
