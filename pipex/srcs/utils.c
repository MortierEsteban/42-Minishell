/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:37:51 by emortier          #+#    #+#             */
/*   Updated: 2022/03/08 09:44:46 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	pipes_error(void)
{
	write (1, "There was an error while trying to use pipe.\n", 45);
}

int	nb_cmds(t_cmd *args)
{
	int	i;

	i = -1;
	while (args[++i].cmd)
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
	path = get_path();
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
