/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:45:28 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/24 16:10:25 by emortier         ###   ########.fr       */
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
	if (pos == -1)
		return (NULL);
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
	char	*tmp;
	char	*p_s;

	if (!ft_strcmp(str, "-"))
	{
		str = ft_get_var_str(env, "OLDPWD");
		if (!str)
		{
			tmp = getcwd((char *) NULL, 0);
			p_s = ft_strdup(tmp);
			free (tmp);
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			g_ex_status = 1;
			return (p_s);
		}
	}
	return (str);
}

void	ft_modif_pwd(char ***env)
{
	char	*path;
	int		pos;

	path = getcwd((char *) NULL, 0);
	pos = ft_find_var(*env, "PWD");
	path = ft_strjoin("PWD=", path);
	if (pos == -1)
		ft_add_env(env, path);
	else
	{
		free ((*env)[pos]);
		(*env)[pos] = ft_strdup_nogc(path);
	}
	gc_free(path);
}

int	ft_cd(char ***env, t_cmd cmd)
{
	char	*newpwd;
	char	*str;
	char	*p_s;
	int		pos;

	str = ft_go2_olpdwd(cmd.cmd[1], env);
	pos = ft_find_var(*env, "OLDPWD");
	p_s = getcwd((char *) NULL, 0);
	newpwd = ft_strjoin("OLDPWD=", p_s);
	if (pos >= 0)
	{
		free((*env)[pos]);
		(*env)[pos] = ft_strdup_nogc(newpwd);
	}
	else
		ft_add_env(env, newpwd);
	gc_free(newpwd);
	free(p_s);
	if (!str)
		str = ft_get_var_str(env, "HOME");
	if (chdir(str) == -1)
		ft_putstr_fd("cd : Invalid or incorrect path\n", STDERR);
	ft_modif_pwd(env);
	return (0);
}
