/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:10:04 by emortier          #+#    #+#             */
/*   Updated: 2022/03/15 12:09:03 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_sort_built(t_cmd arg, char **env)
{
	int	status;

	status = 1;
	if (!ft_strcmp(arg.cmd[0], "exit"))
		status = ft_bexit(arg.cmd, env);
	if (!ft_strcmp(arg.cmd[0], "pwd"))
		status = pwd(1);
	if (!ft_strcmp(arg.cmd[0], "export"))
		status = ft_export(env, arg);
	if (!ft_strcmp(arg.cmd[0], "cd"))
		status = cd(arg.cmd[1]);
	if (!ft_strcmp(arg.cmd[0], "env"))
		status = ft_env(env, 1);
	return (status);
}

int	pipex_process(t_cmd *args, char **env)
{
	int	memory[2];
	int	pipe_exit;
	int	cmdsnb;
	int	i;

	(void) env;
	memory[0] = dup(STDIN);
	memory[1] = dup(STDOUT);
	cmdsnb = nb_cmds(args) - 1;
	pipe_exit = 0;
	i = -1;
	while (++i <= cmdsnb)
	{
		ft_pipex_dup(i, args, memory, &pipe_exit);
		if (ft_sort_built(args[i], env))
			ft_exec(args[i].cmd, env, cmdsnb - i);
	}
	dup2 (memory[0], STDIN);
	dup2 (memory[1], STDOUT);
	close (memory[0]);
	close (memory[1]);
	if (pipe_exit != 0)
		close (pipe_exit);
	return (0);
}
