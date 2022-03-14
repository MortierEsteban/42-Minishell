/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:54:19 by emortier          #+#    #+#             */
/*   Updated: 2022/03/14 13:37:07 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	**ft_envcpy(char **env)
{
	char	**cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	cpy = gc_malloc(sizeof(char *) * i + 1);
	if (!cpy)
		return (NULL);
	i = -1;
	while (env[++i])
		cpy[i] = ft_strdup(env[i]);
	cpy[i] = NULL;
	return (cpy);
}

char	**ft_sort_env(char **env)
{
	char	**sorted;
	char	*swp;
	int		i;

	i = 0;
	sorted = ft_envcpy(env);
	while (sorted[i] && sorted[i + 1])
	{
		if (ft_strcmp(sorted[i], sorted[i + 1]) > 0)
		{
			swp = sorted[i];
			sorted[i] = sorted[i + 1];
			sorted[i + 1] = swp;
			i = 0;
		}
		else
			i++;
	}
	return (sorted);
}

int	ft_cmp_env_varname(char *env, char *var)
{
	int	i;

	i = 0;
	while (env[i] && var[i] && var[i] != '=' && env[i] != '=')
	{
		if (env[i] != var[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_find_var(char **env, char *var)
{
	int	i;

	i = -1;
	while(env[++i])
		if (!ft_cmp_env_varname(env[i], var))
			return (env[i]);
	return (NULL);
}

int	ft_export(char **env, t_cmd cmd)
{
	char	**sorted;
	char	*tmp;
	int		i;

	(void)cmd;
	(void) env;
	sorted = NULL;
	// sorted = ft_sort_env(env);
	i = -1;
	if (cmd.cmd[1] == NULL)
	{
		while (sorted[++i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sorted[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
	else
	{
		while(cmd.cmd[++i])
		{
			tmp = ft_find_var(env, cmd.cmd[i]);
			if (tmp)
			{
				env = ft_envcpy(env);
				if ((tmp = ft_find_var(env, "USER")))
					tmp = ft_strdup("USER=lsidan");
			}
			else
			{
				dprintf(2, "weee");
			}
		}
	}
	return(0);
}
