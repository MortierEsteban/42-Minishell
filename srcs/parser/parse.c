/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:18:37 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/10 13:37:10 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	no_pipe(t_cmd *s_cmd_line, char *str)
{
	int	j;

	j = -1;
	if (!s_cmd_line)
	{
		dprintf(1, "Oops something went wrong.\n");
		return ;
	}
	init_lst(s_cmd_line, 0);
	str = redir(str, &s_cmd_line[0]);
	str = pre_parse_quote(str);
	s_cmd_line[0].cmd = split(str, ' ');
	if (!s_cmd_line)
		return ;
	while (s_cmd_line[0].cmd[++j])
		s_cmd_line[0].cmd[j] = parse_quote(s_cmd_line[0].cmd[j]);
	s_cmd_line[1].cmd = NULL;
}

void	init_lst(t_cmd *cmd, int i)
{
	cmd[i].input = NULL;
	cmd[i].h_doc = NULL;
	cmd[i].output = NULL;
}

void	parse_pipe(t_cmd *s_cmd_line, char *str)
{
	int		i;
	int		j;
	char	**cmd_line;

	i = -1;
	if (!s_cmd_line)
		return (ft_putstr_fd("Oops something went wrong.\n", 2));
	cmd_line = split(str, '|');
	if (!cmd_line)
		return (ft_putstr_fd("Oops something went wrong.\n", 2));
	while (cmd_line && cmd_line[++i])
	{
		init_lst(s_cmd_line, i);
		cmd_line[i] = redir(cmd_line[i], &s_cmd_line[i]);
		dprintf(2, "REDIR : %s\n", cmd_line[i]);
		cmd_line[i] = pre_parse_quote(cmd_line[i]);
		s_cmd_line[i].cmd = split(cmd_line[i], ' ');
		if (!s_cmd_line[i].cmd)
			return (ft_putstr_fd("Oops something went wrong.\n", 2));
		j = -1;
		while (s_cmd_line[i].cmd[++j])
			s_cmd_line[i].cmd[j] = parse_quote(s_cmd_line[i].cmd[j]);
	}
	s_cmd_line[i].cmd = NULL;
}

t_cmd	*parser(char *str)
{
	t_cmd	*s_cmd_line;
	int		c_p;

	if (!str || !ft_strncmp("", str, 1) || is_onlyspace(str))
		return (NULL);
	c_p = count_pipe(str);
	if (c_p == -1)
	{
		s_cmd_line = gc_malloc(sizeof(t_cmd) * 2);
		no_pipe(s_cmd_line, str);
	}
	else if (c_p == -2)
		return (NULL);
	else
	{
		s_cmd_line = gc_malloc(sizeof(t_cmd) * (c_p + 2));
		parse_pipe(s_cmd_line, str);
	}
	return (s_cmd_line);
}
