/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 08:58:53 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/22 08:59:09 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_lst(t_list *head)
{
	t_list	*current;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		gc_free(current->content);
		current = current->next;
	}
}

void	free_cmd(t_cmd	*c_line)
{
	int	i;
	int	j;

	i = -1;
	if (!c_line)
		return ;
	while (c_line[++i].cmd)
	{
		j = -1;
		while (c_line[i].cmd[++j])
			gc_free(c_line[i].cmd[j]);
		c_line[i].state_in = 0;
		c_line[i].state_out = 0;
		free_lst(c_line[i].h_doc);
		free_lst(c_line[i].input);
		free_lst(c_line[i].output);
		gc_free(c_line[i].cmd);
	}
	gc_free(c_line);
}
