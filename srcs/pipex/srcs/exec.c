/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:50 by emortier          #+#    #+#             */
/*   Updated: 2022/03/17 17:46:21 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

unsigned char	g_ex_status = 0;

void	ft_closer(int *redir, int pipes[2])
{
	close (pipes[1]);
	close (pipes[0]);
	close (redir[1]);
	gc_free (redir);
}

void	ft_pipex_dup(int i, t_cmd *args, int memory[2], int *pipe_exit)
{
	int	pipes[2];
	int	cmdsnb;
	int	*redir_fd;

	if (pipe(pipes) == -1)
		pipes_error ();
	redir_fd = redir_handler(args[i], pipe_exit, memory);
	cmdsnb = nb_cmds(args) -1;
	dup2(redir_fd[0], STDIN);
	if (redir_fd[0] != 0)
		close (redir_fd[0]);
	if (*pipe_exit != 0)
		close (*pipe_exit);
	*pipe_exit = dup (pipes[0]);
	if (redir_fd[1] == -1)
	{
		if (i != cmdsnb)
			redir_fd[1] = pipes[1];
		else
			redir_fd[1] = memory[1];
	}
	dup2(redir_fd[1], STDOUT);
	ft_closer(redir_fd, pipes);
}

static void	ft_exit_value(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 2);
	g_ex_status = 130;
}

static void	ft_quit3(int sig)
{
	(void) sig;
	ft_putstr_fd ("Quit: 3\n", 2);
	g_ex_status = 131;
}

void	ft_exec(char **args, char **env, int diff)
{
	pid_t	forks;
	char	*path;
	int		stat;

	signal (SIGINT, ft_exit_value);
	signal (SIGQUIT, ft_quit3);
	forks = fork();
	if (forks == 0)
	{
		path = ft_check_path(args);
		if (path)
		{
			if (execve(path, args, env) == -1)
			{
				dprintf(2, "minishell: Failed to launch binary\n");
				exit (126);
			}
		}
		else
			exit (127);
	}
	else if (!diff)
	{
		waitpid(forks, &stat, 0);
		if (g_ex_status != 130 && g_ex_status != 131)
			g_ex_status = WEXITSTATUS(stat);
	}
	return ;
}
