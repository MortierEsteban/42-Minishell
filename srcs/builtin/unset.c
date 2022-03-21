/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:16:37 by emortier          #+#    #+#             */
/*   Updated: 2022/03/21 15:45:02 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_remove_env(char ***env, int pos)
{
	char	**new_env;
	int		j;
	int		i;

	i = 0;
	j = 0;
	new_env = ft_resize_env(*env, -1);
	while ((*env)[i])
	{
		if (i == pos)
		{
			j = -1;
			free((*env)[i]);
			i++;
			continue ;
		}
		new_env[i + j] = ft_strdup_nogc((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new_env[i + j] = NULL;
	free(*env);
	*env = new_env;
}

int	ft_unset(char ***env, t_cmd cmd)
{
	int		i;
	int		pos;
	char	*error;

	i = -1;
	while (cmd.cmd[++i])
	{
		if (parse_env_name(cmd.cmd[i]))
		{
			error = ft_strjoin("minishell: unset: `", cmd.cmd[i]);
			error = ft_strjoin(error, "'`: not a valid identifier\n");
			ft_putstr_fd(error, 2);
			gc_free (error);
			continue ;
		}
		pos = ft_find_var(*env, cmd.cmd[i]);
		if (pos != -1)
			ft_remove_env(env, pos);
	}
	return (0);
}
//bash: unset: `salut2=': not a valid identifier