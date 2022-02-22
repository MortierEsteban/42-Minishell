/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:55:17 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/18 17:58:44 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	export(char **env, int fd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}
