/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:50 by emortier          #+#    #+#             */
/*   Updated: 2022/03/03 11:00:59 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_pipex_dup(int i, int cmdsnb, int memory[2], int *pipe_exit)
{
	int	pipes[2];

	if (pipe(pipes) == -1)
		pipes_error ();
	dup2(*pipe_exit, STDIN);
	*pipe_exit = dup (pipes[0]);
	if (i != cmdsnb)
		dup2(pipes[1], STDOUT);
	else
		dup2(memory[1], STDOUT);
	close (pipes[0]);
	close (pipes[1]);
}

void	ft_exec(char **args, char **env, int diff)
{
	pid_t	forks;
	char	*path;

	(void) diff;
	forks = fork();
	if (forks == 0)
	{
		path = ft_check_path(args);
		if (path)
			if (execve(path, args, env) == -1)
				dprintf(2, "ERROR WHILE LAUNCHING BINARY\n");
	}
	else if (!diff)
		wait (NULL);
	return ;
}
