/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:55:17 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/03 13:53:40 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	export(char **env, int fd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env[i], fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}
