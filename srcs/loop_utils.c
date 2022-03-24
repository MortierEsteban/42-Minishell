/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 08:43:54 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/24 13:13:39 by emortier         ###   ########.fr       */
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
		current->content = parse_quote(current->content, 0, env);
		current = current->next;
	}	
}

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

void	loop_lst(t_cmd *c_line, char **env)
{
	int	i;

	i = -1;
	while (c_line && c_line[++i].cmd)
	{
		parse_list(c_line[i].input, env);
		parse_list(c_line[i].output, env);
		parse_list(c_line[i].h_doc, env);
		print_debug(c_line, i);
	}	
}
