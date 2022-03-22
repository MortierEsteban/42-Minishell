/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 08:58:09 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/22 08:58:33 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	print(t_list *head)
{
	t_list	*current;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		dprintf(1, "%s\n", (char *)current->content);
		current = current->next;
	}
}

void	print_debug(t_cmd *c_line, int i)
{
	int	j;

	j = 0;
	dprintf(1, ">>>>>>>>> CMD %d : <<<<<<<<<\n", i);
	while (c_line && c_line[i].cmd && c_line[i].cmd[j])
		dprintf(1, "SPLITTED = %s\n", c_line[i].cmd[j++]);
	j = 0;
	dprintf(1, ">>>>>>>>> INPUT %d : <<<<<<<<<\n", i);
	print(c_line[i].input);
	dprintf(1, ">>>>>>>>> OUTPUT %d : <<<<<<<<<\n", i);
	print(c_line[i].output);
	dprintf(1, ">>>>>>>>> H_DOC %d : <<<<<<<<<\n", i);
	print(c_line[i].h_doc);
}
