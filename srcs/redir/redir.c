/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/24 12:54:22 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	*redir_handler(t_cmd cmd, int *pipe_exit, int memory[2])
{
	int		*final_fd;

	final_fd = ft_redirects(cmd, memory);
	dprintf(2, "redir: 0 = %d, 1 = %d\n, state = 0= %d, 1 = %d\n", final_fd[0], final_fd[1], cmd.state_in, cmd.state_out);
	if ((final_fd[0] == -1 && cmd.state_in != 0) || \
		(final_fd[1] == -1 && cmd.state_out != 0))
		return (NULL);
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
	if (args.state_in == 1 && !ft_path_exists(ft_lstlast(args.input)))
			fds[0] = open((ft_lstlast(args.input))->content, O_RDONLY);
	if (args.state_in == 2 && args.hdoc_fd != -1)
		fds[0] = args.hdoc_fd;
	while (args.output && args.output->next)
	{
		if (ft_path_exists(args.output))
			return (fds);
		ft_touch_files(args.output->content);
		args.output = args.output->next;
	}
	if (args.state_out == 1 && !ft_path_exists(args.output))
		fds[1] = open(args.output->content, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (args.state_out == 2 && !ft_path_exists(args.output))
		fds[1] = open(args.output->content, \
		O_APPEND | O_WRONLY | O_CREAT, 0777);
	return (fds);
}
