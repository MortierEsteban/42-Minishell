/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:45:28 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/16 14:20:05 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_get_var_str(char ***env, char *var)
{
	int		pos;
	char	*pwd;
	int		i;

	i = 0;
	pos = ft_find_var(*env, var);
	while ((*env)[pos][i] && (*env)[pos][i] != '=')
		i++;
	if ((*env)[pos][i] == '=')
	{
		pwd = ft_strdup((*env)[pos] + i + 1);
		return (pwd);
	}
	return (NULL);
}

char	*ft_go2_olpdwd(char *str, char ***env)
{
	if (!ft_strcmp(str, "-"))
	{
		str = ft_get_var_str(env, "OLDPWD");
		if (!str)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			g_ex_status = 1;
			return (0);
		}
		str = ft_strjoin(str, "/");
	}
	return (str);
}

int	cd(char *str, char ***env)
{
	char	*newpwd;
	int		pos;

	str = ft_go2_olpdwd(str, env);
	if (str == NULL)
		return (0);
	pos = ft_find_var(*env, "OLDPWD");
	if (pos >= 0)
	{
		newpwd = getcwd((char *) NULL, 0);
		free((*env)[pos]);
		(*env)[pos] = ft_strdup_nogc(ft_strjoin("OLDPWD=", newpwd));
	}
	if (!str)
		str = *env[ft_find_var(*env, "HOME")];
	if (chdir(str) == -1)
	{
		ft_putstr_fd("cd : Invalid or incorrect path\n", STDERR);
		return (0);
	}
	return (0);
}
