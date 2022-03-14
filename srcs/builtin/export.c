/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:54:19 by emortier          #+#    #+#             */
/*   Updated: 2022/03/14 08:28:40 by lsidan           ###   ########lyon.fr   */
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

int	ft_export(char **env, t_cmd cmd)
{
	char	**sorted;
	int		i;

	(void)cmd;
	(void) env;
	sorted = NULL;
	// sorted = ft_sort_env(env);
	i = -1;
	while (sorted[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sorted[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
