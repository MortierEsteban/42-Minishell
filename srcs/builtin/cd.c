/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:45:28 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/12 13:40:51 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	cd(const char *str)
{
	static char	*oldpwd = NULL;
	char		*tmp;

	tmp = getcwd((char *) NULL, 0);
	if (!ft_strcmp(str, "-"))
	{
		if (oldpwd)
			str = oldpwd;
		else
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			g_ex_status = 1;
			return (0);
		}
	}
	if (!str)
		str = getenv("HOME");
	if (chdir(str) == -1)
	{
		ft_putstr_fd("cd : Invalid or incorrect path\n", STDERR);
		return (1);
	}
	oldpwd = tmp;
	return (0);
}
