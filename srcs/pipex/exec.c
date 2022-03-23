/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:50 by emortier          #+#    #+#             */
/*   Updated: 2022/03/23 15:12:04 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

unsigned char	g_ex_status = 0;

void	ft_closer(int *redir, int pipes[2])
{
	close (pipes[1]);
	close (pipes[0]);
	close (redir[1]);
	gc_free (redir);
}

int	ft_pipex_dup(int i, t_cmd *args, int memory[2], int *pipe_exit)
{
	int	pipes[2];
	int	cmdsnb;
	int	*redir_fd;

	if (pipe(pipes) == -1)
		write (1, "There was an error while trying to use pipe.\n", 45);
	redir_fd = redir_handler(args[i], pipe_exit, memory);
	if (redir_fd == NULL)
		return (1);
	cmdsnb = nb_cmds(args) -1;
	dup2(redir_fd[0], STDIN);
	if (redir_fd[0] != 0)
		close (redir_fd[0]);
	if (*pipe_exit != 0)
		close (*pipe_exit);
	*pipe_exit = dup (pipes[0]);
	ft_norm_pdup(&redir_fd, memory, pipes, cmdsnb - i);
	dup2(redir_fd[1], STDOUT);
	ft_closer(redir_fd, pipes);
	return (0);
}

void	ft_get_exit_stat(pid_t forks)
{
	int	stat;

	waitpid(forks, &stat, 0);
	if (g_ex_status != 130 && g_ex_status != 131)
		g_ex_status = WEXITSTATUS(stat);
}

int	ft_perror(void)
{
	ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
	return (1);
}

int	ft_exec(char **args, char **env, int diff)
{
	pid_t	forks;
	char	*path;

	forks = fork();
	if (forks < 0)
		return (ft_perror());
	if (forks == 0)
	{
		path = ft_check_path(args);
		if (path)
		{
			if (execve(path, args, env) == -1)
			{
				ft_putstr_fd("minishell: Failed to launch binary\n", 2);
				exit (126);
			}
		}
		else
			exit (127);
	}
	else if (!diff)
		ft_get_exit_stat(forks);
	return (0);
}
