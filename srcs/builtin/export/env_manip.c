/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:54:19 by emortier          #+#    #+#             */
/*   Updated: 2022/03/22 10:34:27 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

char	**ft_envcpy(char **env, int p_s)
{
	char	**cpy;
	int		pos;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (i == 0)
		return (ft_recreate_env());
	cpy = malloc(sizeof(char *) * (i + 1));
	if (!cpy)
		return (NULL);
	i = -1;
	while (env[++i])
		cpy[i] = ft_strdup_nogc(env[i]);
	cpy[i] = NULL;
	if (p_s)
	{
		ft_shlvl(&cpy);
		pos = ft_find_var(env, "OLDPWD");
		if (pos >= 0)
			ft_remove_env(&cpy, pos);
		ft_add_env(&cpy, "OLDPWD");
	}
	return (cpy);
}

char	**ft_sort_env(char **env)
{
	char	**sorted;
	char	*swp;
	int		i;

	i = 0;
	sorted = ft_envcpy(env, 0);
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

int	parse_env_name(char *varname)
{
	int	i;

	i = 0;
	if (!varname)
		return (1);
	if (ft_isdigit(varname[0]) || !stop(varname[0], TABLE2))
		return (1);
	while (varname[i] && varname[i] != '=')
	{
		if (!stop(varname[i], TABLE2))
			return (1);
		i++;
	}
	return (0);
}

int	ft_cmp_env_varname(char *env, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] && var[i] && var[i] != '=' && env[i] != '=')
	{
		if (env[i] != var[i])
			return (1);
		i++;
	}
	j = i;
	if (env[i] == '=' || env[i] == '\0')
		i--;
	if (var[j] == '=' || var[j] == '\0')
		j--;
	if (env[i] == var[j])
		return (0);
	return (1);
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
