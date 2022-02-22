/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:45:28 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/18 17:48:11 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	cd(const char *str)
{
	if (!str)
	{
		ft_putstr_fd("cd : Error\n", STDERR);
		return (1);
	}
	if (chdir(str) == -1)
	{
		ft_putstr_fd("cd : Invalid or incorrect path\n", STDERR);
		return (1);
	}
	return (0);
}
