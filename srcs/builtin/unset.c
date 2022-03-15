/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:16:37 by emortier          #+#    #+#             */
/*   Updated: 2022/03/15 17:23:41 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_remove_env(char ***env, int pos)
{
	char	**new_env;
	int		j;
	int		i;

	i = -1;
	j = 0;
	new_env = ft_resize_env(*env, -1);
	while ((*env)[++i])
	{
		if (i == pos)
		{
			j = -1;
			continue ;
		}
		new_env[i + j] = ft_strdup_nogc((*env)[i]);
		free((*env)[i]);
	}
	new_env[i + j] = NULL;
	free(*env);
	*env = new_env;
}

int	ft_unset(char ***env, t_cmd cmd )
{
	int		i;
	int		pos;

	i = -1;
	while (cmd.cmd[++i])
	{
		pos = ft_find_var(*env, cmd.cmd[i]);
		if (pos == -1)
			continue ;
		ft_remove_env(env, pos);
	}
	return (0);
}
