/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/09 13:24:42 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_touch_files(char *filename)
{
	int	fd;

	fd = 0;
	if (access(filename, F_OK))
		fd = open(filename, O_CREAT, 0777);
	close (fd);
}

int	*ft_redirects(t_cmd args)
{
	int	*fds;

	fds = gc_malloc(sizeof(int) * 2);
	fds[0] = -1;
	fds[1] = -1;
	if (args.state_in == 1)
		fds[0] = open((ft_lstlast(args.input))->content, O_RDONLY);
	while (args.output && args.output->next)
	{
		ft_touch_files(args.output->content);
		args.output = args.output->next;
	}
	if (args.state_out == 1 && ft_strcmp(args.output->content, ""))
		fds[1] = open(args.output->content, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (args.state_out == 2)
		fds[1] = open(args.output->content, \
		O_APPEND | O_WRONLY | O_CREAT, 0777);
	return (fds);
}
