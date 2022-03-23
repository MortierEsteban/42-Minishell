/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 08:43:54 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/23 13:23:12 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	nothing(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	s_machine_quote(char *str, int i)
{
	static int	_q = 0;

	if (str[i] == '\'' && !_q)
		_q = 1;
	else if (str[i] == '\"' && !_q)
		_q = 2;
	else if ((str[i] == '\"' && _q == 2) || (str[i] == '\'' && _q == 1))
		_q = 0;
	return (_q);
}

void	parse_list(t_list *head, char **env)
{
	t_list	*current;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		current->content = parse_quote(current->content, 1, env);
		current = current->next;
	}	
}

void	loop_lst(t_cmd *c_line, char **env)
{
	int	i;

	i = -1;
	while (c_line && c_line[++i].cmd)
	{
		parse_list(c_line[i].input, env);
		parse_list(c_line[i].output, env);
		parse_list(c_line[i].h_doc, env);
	}	
}
