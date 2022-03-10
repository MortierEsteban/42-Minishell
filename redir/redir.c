/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/10 14:46:39 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	*redir_handler(t_cmd cmd, int *pipe_exit, int memory[2])
{
	int	*final_fd;
	int	i;

	i = -1;
	final_fd = ft_redirects(cmd, memory);
	if (final_fd[0] == -1)
		final_fd[0] = *pipe_exit;
	return (final_fd);
}
