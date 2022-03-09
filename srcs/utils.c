/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:53:03 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 17:03:38 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**get_path(void)
{
	char	**path;
	char	*str;
	int		i;

	i = -1;
	str = getenv("PATH");
	path = ft_split(str, ':');
	if (!path)
		return (NULL);
	return (path);
}

char	*get_env_var(char *var)
{
	char	*str;

	str = getenv(var);
	gc_free(var);
	return (str);
}

char	***create_var_tab(char **env)
{
	int		i;
	char	***var;

	i = -1;
	while (env[++i])
		i++;
	var = gc_malloc(sizeof(char *) * (i + 2));
	var[i] = 0;
	i = -1;
	while (env[++i])
	{
		var[i] = ft_split(env[i], '=');
		dprintf(1, "%s\n", *var[i]);
	}
	return (var);
}

int	is_onlyspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}
