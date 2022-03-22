/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:10:04 by emortier          #+#    #+#             */
/*   Updated: 2022/03/22 15:43:03 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_fork_bins(char ***env, t_cmd cmd, int (*builtin)(char ***env, t_cmd cmd))
{
	pid_t	forks;

	forks = fork();
	if (forks == 0)
	{
		if (builtin(env, cmd) == 1)
		{
			ft_putstr_fd("minishell: Builtin Failed\n", 2);
			exit (126);
		}
		exit(0);
	}
	else
		ft_get_exit_stat(forks);
	return (0);
}

int	ft_isonlycmd(t_cmd arg, char ***env)
{
	int	status;

	status = -1;
	if (!ft_strcmp(arg.cmd[0], "export"))
		status = ft_export(env, arg);
	if (!ft_strcmp(arg.cmd[0], "exit"))
		status = ft_bexit(env, arg);
	if (!ft_strcmp(arg.cmd[0], "cd"))
		status = ft_cd(env, arg);
	if (!ft_strcmp(arg.cmd[0], "unset"))
		status = ft_unset(env, arg);
	if (status >= 0)
		g_ex_status = status;
	return (status);
}

int	ft_sort_built(t_cmd arg, char ***env, int p_s)
{
	int	status;

	status = -1;
	if (!ft_strcmp(arg.cmd[0], "env"))
		status = ft_fork_bins(env, arg, ft_env);
	if (!ft_strcmp(arg.cmd[0], "echo"))
		status = ft_fork_bins(env, arg, ft_echo);
	if (!ft_strcmp(arg.cmd[0], "pwd"))
		status = ft_fork_bins(env, arg, ft_pwd);
	if (p_s == 0)
		return (ft_isonlycmd(arg, env));
	dprintf(2, "didn4t use onlycmd");
	if (!ft_strcmp(arg.cmd[0], "export"))
		status = ft_fork_bins(env, arg, ft_export);
	if (!ft_strcmp(arg.cmd[0], "exit"))
		status = ft_fork_bins(env, arg, ft_bexit);
	if (!ft_strcmp(arg.cmd[0], "cd"))
		status = ft_fork_bins(env, arg, ft_cd);
	if (!ft_strcmp(arg.cmd[0], "unset"))
		status = ft_fork_bins(env, arg, ft_unset);
	if (status >= 0)
		g_ex_status = status;
	return (status);
}

int	ft_close_fd_process(int memory[2], int pipe_exit, t_cmd *args)
{
	int	i;

	i = -1;
	while (args[++i].cmd)
		if (args[i].hdoc_fd != -1)
			close(args[i].hdoc_fd);
	dup2 (memory[0], STDIN);
	dup2 (memory[1], STDOUT);
	close (memory[0]);
	close (memory[1]);
	if (pipe_exit != 0)
		close (pipe_exit);
	return (1);
}

int	pipex_process(t_cmd *args, char ***env)
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
	g_ex_status = 0;
	i = -1;
	signal(SIGINT, ft_ctrlc_hdoc);
	while (++i <= cmdsnb)
	{
		args[i].hdoc_fd = -1;
		if (args[i].state_in == 2)
		{
			args[i].hdoc_fd = ft_heredoc(args[i], memory);
			if (args[i].hdoc_fd == -1)
				return (1);
		}
	}
	i = -1;
	signal (SIGINT, ft_exec_ctrlc);
	signal (SIGQUIT, ft_quit3);
	while (++i <= cmdsnb)
	{
		ft_pipex_dup(i, args, memory, &pipe_exit);
		if (ft_sort_built(args[i], env, cmdsnb))
			if (ft_exec(args[i].cmd, *env, cmdsnb - i))
				return (ft_close_fd_process(memory, pipe_exit, args));
	}
	i = 0;
	ft_close_fd_process(memory, pipe_exit, args);
	while (i != -1)
		i = wait(NULL);
	return (0);
}
