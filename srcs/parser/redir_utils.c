/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:41:57 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/10 12:15:45 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	input_case(t_cmd *cmd, char *tmp, t_list *l_tmp)
{
	if (!cmd->input)
	{
		cmd->state_in = 1;
		cmd->input = ft_lstnew((void *) tmp);
	}
	else
	{
		cmd->state_in = 1;
		l_tmp = ft_lstlast(cmd->input);
		ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
	}
}

void	heredoc_case(t_cmd *cmd, char *tmp, t_list *l_tmp)
{
	if (!cmd->h_doc)
	{
		cmd->state_in = 2;
		cmd->h_doc = ft_lstnew((void *) tmp);
	}
	else
	{
		cmd->state_in = 2;
		l_tmp = ft_lstlast(cmd->h_doc);
		ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
	}
}

void	output_case(t_cmd *cmd, char *tmp, t_list *l_tmp)
{
	if (!cmd->output)
	{
		cmd->state_out = 1;
		cmd->output = ft_lstnew((void *) tmp);
	}
	else
	{
		cmd->state_out = 1;
		l_tmp = ft_lstlast(cmd->output);
		ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
	}
}

void	append_case(t_cmd *cmd, char *tmp, t_list *l_tmp)
{
	if (!cmd->output)
	{
		cmd->state_out = 2;
		cmd->output = ft_lstnew((void *) tmp);
	}
	else
	{
		cmd->state_out = 2;
		l_tmp = ft_lstlast(cmd->output);
		ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
	}
}

void	which_case(t_cmd *cmd, char *tmp, char c, char d)
{
	t_list	*l_tmp;

	l_tmp = NULL;
	if (!ft_strcmp(tmp, ""))
		return (ft_putstr_fd("cassé", 2));
	if (c == '<' && !d)
		input_case(cmd, tmp, l_tmp);
	else if (c == '<' && d)
		heredoc_case(cmd, tmp, l_tmp);
	else if (c == '>' && !d)
		output_case(cmd, tmp, l_tmp);
	else if (c == '>' && d)
		append_case(cmd, tmp, l_tmp);
}
