/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:55:17 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/21 15:45:23 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(char ***env, t_cmd cmd)
{
	int	i;

	(void) cmd;
	i = -1;
	while (*env[++i])
	{
		if (ft_strchr(*env[i], '='))
		{
			ft_putstr_fd(*env[i], 1);
			ft_putchar_fd('\n', 1);
		}
	}
	return (0);
}
