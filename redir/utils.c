/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/10 17:21:55 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_heredoc(t_cmd arg, int memory[2])
{
	char	*line;
	char	*tmp;
	int		pipes[2];
	pid_t	forks;

	if (pipe(pipes) == -1)
		pipes_error();
	dprintf(2, "pipes[0] = %d ; pipe[1] =%d\n", pipes[0], pipes[1]);
	forks = fork();
	if (forks == 0)
	{
		dup2(memory[0], STDIN);
		dup2(memory[1], STDOUT);
		while (arg.h_doc->next)
		{
			dprintf(2, "current = %s\n", arg.h_doc->content);
			line = readline("<");
			if (!ft_strcmp(line, arg.h_doc->content))
				arg.h_doc = arg.h_doc->next;
			free (line);
		}
		while (42)
		{
			dprintf(2, "Current = |%s|\n", arg.h_doc->content);
			line = readline("final<");
			tmp = ft_strdup(line);
			free(line);
			line = tmp;
			line = parse_quote(line);
			if (ft_strcmp(line, arg.h_doc->content))
			{
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

	fds = gc_malloc(sizeof(int) * 2);
	fds[0] = -1;
	fds[1] = -1;
	if (args.state_in == 1)
		fds[0] = open((ft_lstlast(args.input))->content, O_RDONLY);
	if (args.state_in == 2)
		fds[0] = ft_heredoc(args, memory);
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
