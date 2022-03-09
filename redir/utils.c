/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/08 13:20:32 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_touch_files(char *filename)
{
	char	**touch;

	touch = gc_malloc(sizeof(char *) * 3);
	if (!touch)
		return ;
	touch[2] = NULL;
	touch[0] = ft_strdup("touch");
	touch[1] = ft_strdup(filename);
	ft_exec(touch, 0, 42);
	gc_free(touch[0]);
	gc_free(touch[1]);
	gc_free(touch);
}

int	*ft_redirects(t_cmd args)
{
	int	*fds;
	(void) args;

	fds = gc_malloc(sizeof(int) * 2);
	fds[0] = -1;
	fds[1] = -1;
	if (args.state_in == 1)
		fds[0] = open((ft_lstlast(args.input))->content, O_RDONLY);
	while (args.output && args.output->next)
	{
		dprintf(1, "SA MERE");
		ft_touch_files(args.output->content);
		args.output = args.output->next;
	}
	if (args.output)
		ft_touch_files(args.output->content);
	if (args.state_out == 1)
		fds[1] = open(args.output->content, O_WRONLY);
	else if (args.state_out == 2)
		fds[1] = open(args.output->content, O_APPEND);
	return (fds);
}
