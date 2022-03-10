/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:50 by emortier          #+#    #+#             */
/*   Updated: 2022/03/10 11:30:26 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	g_ret_val = -1;

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
	redir_fd = redir_handler(args[i], pipe_exit);
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

void	ft_exec(char **args, char **env, int diff)
{
	pid_t	forks;
	char	*path;

	forks = fork();
	if (forks == 0)
	{
		path = ft_check_path(args);
		if (path)
		{
			if (execve(path, args, env) == -1)
			{
				g_ret_val = 0;
				return ;
			}
			else
				g_ret_val = 1;
		}
		else
			dprintf(2, "TROUBLE WHEN FINDING BINARY");
		
	}
	else if (!diff)
	{
		if (!ft_check_path(args))
			kill (forks, SIGTERM);
		waitpid(forks, 0, 0);
	}
	return ;
}
