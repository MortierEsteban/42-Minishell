/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/08 16:15:40 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	*redir_handler(t_cmd cmd, int *pipe_exit)
{
	int	*final_fd;
	int	i;

	i = -1;
	final_fd = ft_redirects(cmd);
	if (final_fd[0] == -1)
		final_fd[0] = *pipe_exit;
	return (final_fd);
}
