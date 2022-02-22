/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:53:03 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/22 11:08:40 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**get_env_var(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_split(&env[i][5], ':');
			if (!path)
				return (NULL);
			break ;
		}
	}
	return (path);
}
