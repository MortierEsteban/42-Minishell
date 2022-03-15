/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:55:17 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/15 13:21:44 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(char **env, int fd)
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
