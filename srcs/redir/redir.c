/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/23 13:15:00 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	*redir_handler(t_cmd cmd, int *pipe_exit, int memory[2])
{
	int	*final_fd;

	final_fd = ft_redirects(cmd, memory);
	if (final_fd[0] == -1)
		final_fd[0] = *pipe_exit;
	return (final_fd);
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
	if (args.state_in == 1 && !access(ft_lstlast(args.input)->content, F_OK))
		fds[0] = open((ft_lstlast(args.input))->content, O_RDONLY);
	if (args.state_in == 2 && args.hdoc_fd != -1)
		fds[0] = args.hdoc_fd;
	while (args.output && args.output->next)
	{
		ft_touch_files(args.output->content);
		args.output = args.output->next;
	}
	if (args.state_out == 1)
		fds[1] = open(args.output->content, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (args.state_out == 2)
		fds[1] = open(args.output->content, \
		O_APPEND | O_WRONLY | O_CREAT, 0777);
	return (fds);
}
