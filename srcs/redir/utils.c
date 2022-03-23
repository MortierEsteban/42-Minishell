/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/23 13:19:20 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_final_doc(int pipes[2], char *filename)
{
	char	*line;
	char	*tmp;

	while (42)
	{
		line = readline("> ");
		tmp = ft_strdup(line);
		free(line);
		line = tmp;
		if (ft_strcmp(line, filename))
		{
			line = pre_parse_quote(line, 0);
			ft_putstr_fd(line, pipes[1]);
			ft_putchar_fd('\n', pipes[1]);
		}
		else
		{
			gc_free(line);
			break ;
		}
		gc_free(line);
	}
}

void	ft_pre_hdoc(t_cmd arg)
{
	char	*line;

	while (arg.h_doc->next)
	{
		line = readline("> ");
		if (!ft_strcmp(line, arg.h_doc->content))
			arg.h_doc = arg.h_doc->next;
		free (line);
	}
}

void	ft_wrap_hdoc(t_cmd arg, int memory[2], int pipes[2])
{
	signal(SIGQUIT, ft_rm_sig_chars);
	signal(SIGINT, ft_sig_hdoc);
	dup2(memory[0], STDIN);
	dup2(memory[1], STDOUT);
	ft_pre_hdoc(arg);
	ft_final_doc (pipes, ft_lstlast(arg.h_doc)->content);
	if (arg.hdoc_fd == -1)
		exit (1);
	exit (0);
}

int	ft_heredoc(t_cmd arg, int memory[2])
{
	int		pipes[2];
	pid_t	forks;

	if (pipe(pipes) == -1)
		write (1, "There was an error while trying to use pipe.\n", 45);
	signal(SIGINT, ft_do_endl);
	signal(SIGQUIT, ft_sig_hdoc);
	forks = fork();
	if (forks < 0)
	{
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		return (-1);
	}
	if (forks == 0)
		ft_wrap_hdoc(arg, memory, pipes);
	else
	{
		waitpid(forks, NULL, 0);
		close (pipes[1]);
		return (pipes[0]);
	}
	return (1);
}
