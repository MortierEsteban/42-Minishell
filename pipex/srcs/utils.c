/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:37:51 by emortier          #+#    #+#             */
/*   Updated: 2022/03/02 10:38:09 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	pipes_error(void)
{
	write (1, "There was an error while trying to use pipe.\n", 45);
}

int	nb_cmds(char ***args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
	}
	return (i);
}

char	*ft_check_path(char **args)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	path = get_env_var();
	if (path == NULL)
		return (NULL);
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], args[0]);
	}
	i = -1;
	while (path[++i])
	{
		if (close ((open (path[i], O_RDONLY))) != -1)
			return (path[i]);
	}
	return (NULL);
}
