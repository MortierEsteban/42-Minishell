/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:26:25 by emortier          #+#    #+#             */
/*   Updated: 2022/03/17 07:19:50 by lsidan           ###   ########.fr       */
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
