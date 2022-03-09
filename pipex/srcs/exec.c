/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:50 by emortier          #+#    #+#             */
/*   Updated: 2022/03/08 18:38:56 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_pipex_dup(int i, t_cmd *args, int memory[2], int *pipe_exit)
{
	int	pipes[2];
	int	cmdsnb;
	int	*redir_fd;

	if (pipe(pipes) == -1)
		pipes_error ();
	redir_fd = redir_handler(args[i], pipe_exit);
	cmdsnb = nb_cmds(args) -1;
	dup2(*pipe_exit, STDIN);
	if (*pipe_exit != 0)
		close (*pipe_exit);
	*pipe_exit = dup (pipes[0]);
	dprintf(1, "0 = %d , 1 = %d\n", redir_fd[0], redir_fd[1]);
	if (i != cmdsnb)
		redir_fd[1] = pipes[1];
	else
		redir_fd[1] = memory[1];
	dup2(redir_fd[1], STDOUT);
	close (redir_fd[1]);
	close (pipes[0]);
	close (pipes[1]);
	gc_free (redir_fd);
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
			if (execve(path, args, env) == -1)
				dprintf(2, "ERROR WHILE LAUNCHING BINARY\n");
	}
	else if (!diff)
		wait(NULL);
	return ;
}
