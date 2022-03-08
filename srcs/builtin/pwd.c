/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:36:41 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/02 19:50:54 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	pwd(int fd)
{
	char	*dir;

	if (fd < 0 || fd > 99998)
		return (1);
	dir = getcwd((char *) NULL, 0);
	if (!dir)
	{
		ft_putstr_fd("Error\n", STDERR);
		return (1);
	}
	ft_putstr_fd(dir, fd);
	ft_putchar_fd('\n', fd);
	free(dir);
	return (0);
}
