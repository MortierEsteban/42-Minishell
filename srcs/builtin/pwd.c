/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:36:41 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/21 15:47:26 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_pwd(char ***env, t_cmd cmd)
{
	char	*dir;

	(void) env;
	(void) cmd;
	dir = getcwd((char *) NULL, 0);
	if (!dir)
	{
		ft_putstr_fd("Error\n", STDERR);
		return (1);
	}
	ft_putstr_fd(dir, 1);
	ft_putchar_fd('\n', 1);
	free(dir);
	return (0);
}
