/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:10:04 by emortier          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/23 14:26:37 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
/*   Updated: 2022/02/22 13:05:10 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/pipex.h"
>>>>>>> bc44b75067959c3ca88369fae608fbc85871a112
#include "../incl/minishell.h"

		//ft_checkallpath + find .bin + check.binchmod + dup if >else if >> append
char	*ft_check_path(char **args, char **env)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	path = get_env_var(env);
	if (path == NULL)
		return (NULL);
	while (path[++i])
<<<<<<< HEAD
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], args[0]);
	}
	i = -1;
	while (path[++i])
	{
		if (close ((open (path[i], O_RDONLY))) != -1)
			return (path[i]);
	}
=======
		ft_strjoin(path[i], args[0]);
	i = -1;
	while (path[++i])
		if(close (open (path[i], O_RDONLY)))
			return (path);
>>>>>>> bc44b75067959c3ca88369fae608fbc85871a112
	return (NULL);
}

void	pipes_error(int *pipes[2], int i)
{
	int	j;

	j = -1;
	while (++j <= i)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	write (2, "There was an error while trying to use pipe.\n", 45);
}

void	ft_exec(char **args, char **env)
{
	pid_t	forks;
	char	*path;

	forks = fork();
	if (forks == 0)
	{
		path = ft_check_path(args, env);
<<<<<<< HEAD
		dprintf(1, "EXEC : %s \nPATH : %s\n", args[0], path);
		if (path)
			execve(path, args, env);
	}
	return ;
=======
		if (path)
			execve(path, args, env);
	}
	return (0);
>>>>>>> bc44b75067959c3ca88369fae608fbc85871a112
}

int	nb_cmds(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
	}	
	return (i);
}

int	pipex_process(char ***args, char **env)
{
	int	cmdsnb;
	int	i;
	// int	*pipes[2];

	cmdsnb = nb_cmds(*args);
	i = -1;
	// while (++i < cmdsnb)
	// 	if (pipe(pipes[i]) == -1)
	// 		pipe_error(pipes, i);
	i = -1;
	while (++i < cmdsnb)
		ft_exec(args[i], env);
<<<<<<< HEAD
	return (0);
=======
>>>>>>> bc44b75067959c3ca88369fae608fbc85871a112
}
