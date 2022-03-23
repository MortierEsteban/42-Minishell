/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/22 16:46:44 by lsidan           ###   ########.fr       */
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

int	ft_heredoc(t_cmd arg, int memory[2])
{
	int		pipes[2];
	pid_t	forks;

	if (pipe(pipes) == -1)
		pipes_error();
	forks = fork();
	if (forks < 0)
	{
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		return (-1);
	}
	if (forks == 0)
	{
		dup2(memory[0], STDIN);
		dup2(memory[1], STDOUT);
		ft_pre_hdoc(arg);
		ft_final_doc (pipes, ft_lstlast(arg.h_doc)->content);
		if (arg.hdoc_fd == -1)
			exit (1);
		exit (0);
	}
	else
	{
		waitpid(forks, NULL, 0);
		close (pipes[1]);
		return (pipes[0]);
	}
}

void	ft_touch_files(char *filename)
{
	int	fd;

	fd = 0;
	if (access(filename, F_OK))
		fd = open(filename, O_CREAT, 0777);
	close (fd);
}

int	*ft_redirects(t_cmd args, int memory[2])
{
	int	*fds;

	(void) memory;
	fds = gc_malloc(sizeof(int) * 2);
	fds[0] = -1;
	fds[1] = -1;
	if (args.state_in == 1)
		fds[0] = open((ft_lstlast(args.input))->content, O_RDONLY);
	if (args.state_in == 2 && args.hdoc_fd != -1)
		fds[0] = args.hdoc_fd;
	while (args.output && args.output->next)
	{
		ft_touch_files(args.output->content);
		args.output = args.output->next;
	}
	if (args.state_out == 1 && ft_strcmp(args.output->content, ""))
		fds[1] = open(args.output->content, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (args.state_out == 2 && ft_strcmp(args.output->content, ""))
		fds[1] = open(args.output->content, \
		O_APPEND | O_WRONLY | O_CREAT, 0777);
	return (fds);
}
