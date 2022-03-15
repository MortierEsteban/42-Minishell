/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:54:19 by emortier          #+#    #+#             */
/*   Updated: 2022/03/15 13:40:07 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_strdup_nogc(char *s1)
{
	size_t		i;
	char		*s2;

	i = 0;
	s2 = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	else
	{
		while (s1[i])
		{
			s2[i] = s1[i];
			i++;
		}
	}
	s2[i] = '\0';
	return (s2);
}

char	**ft_envcpy(char **env)
{
	char	**cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		cpy[i] = ft_strdup_nogc(env[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

char	**ft_add_quotes(char **sorted)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	while (sorted[++i])
	{
		tmp = ft_split(sorted[i], '=');
		if (!tmp)
			return (NULL);
			free(sorted[i]);
			sorted[i] = ft_strjoin(tmp[0], "=\"");
			if (tmp[1])
				sorted[i] = ft_strjoin(sorted[i], tmp[1]);
			sorted[i] = ft_strjoin(sorted[i], "\"\n");
		j = 0;
		while(tmp[j])
			free (tmp[j++]);
		free (tmp);
	}
	return (sorted);
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
	ft_add_quotes(sorted);
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

int	ft_find_var(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_cmp_env_varname(env[i], var))
			return (i);
	return (-1);
}

void	ft_free_sorted(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		gc_free(env[i]);
	free (env);
}

int	ft_export(char **env, t_cmd cmd)
{
	char	**sorted;
	int		tmp;
	int		i;

	(void)cmd;
	(void) env;
	sorted = NULL;
	if (cmd.cmd[1] == NULL)
	{
		i = 0;
		sorted = ft_sort_env(env);
		while (sorted && sorted[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sorted[i], 1);
			if (!ft_strchr(sorted[i], '='))
				ft_putstr_fd("\n", 1);
			i++;
		}
		ft_free_sorted (sorted);
	}
	else
	{
		i = 0;
		while (cmd.cmd[++i])
		{
			tmp = ft_find_var(env, cmd.cmd[i]);
			dprintf(2, "found %s\n",env[tmp]);
			if (tmp >= 0 && ft_strchr(cmd.cmd[i], '='))
			{
				free(env[tmp]);
				env[tmp] = ft_strdup_nogc(cmd.cmd[i]);
			}
			// else
			// 	ft_add_env(cmd.cmd[i]);
		}
	}
	return (0);
}
