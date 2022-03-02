/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:10:04 by emortier          #+#    #+#             */
/*   Updated: 2022/03/02 10:39:51 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	pipex_process(char ***args, char **env)
{
	int	memory[2];
	int	pipe_exit;
	int	cmdsnb;
	int	i;

	memory[0] = dup(STDIN);
	memory[1] = dup(STDOUT);
	cmdsnb = nb_cmds(args) - 1;
	pipe_exit = 0;
	i = -1;
	while (++i <= cmdsnb)
	{
		ft_pipex_dup(i, cmdsnb, memory, &pipe_exit);
		ft_exec(args[i], env, cmdsnb - i);
	}
	dup2 (memory[0], STDIN);
	return (0);
}
