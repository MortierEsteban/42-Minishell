/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:54:19 by emortier          #+#    #+#             */
/*   Updated: 2022/03/15 16:24:08 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

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
