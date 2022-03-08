/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:53:03 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/03 09:41:03 by lsidan           ###   ########lyon.fr   */
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
	return (str);
}
