/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:18:37 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/23 11:35:46 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	no_pipe(t_cmd *s_cmd_line, char *str, char **env)
{
	int	j;

	j = -1;
	if (!s_cmd_line)
		return (1);
	init_lst(s_cmd_line, 0);
	str = redir(str, &s_cmd_line[0]);
	if (!str)
		return (1);
	str = pre_parse_quote(str, env);
	dprintf(1, "%s\n", str);
	s_cmd_line[0].cmd = split(str, ' ');
	if (!s_cmd_line[0].cmd)
		return (1);
	while (s_cmd_line[0].cmd[++j])
		s_cmd_line[0].cmd[j] = parse_quote(s_cmd_line[0].cmd[j], 1, env);
	gc_free(str);
	s_cmd_line[1].cmd = NULL;
	return (0);
}

void	init_lst(t_cmd *cmd, int i)
{
	cmd[i].input = NULL;
	cmd[i].h_doc = NULL;
	cmd[i].output = NULL;
	cmd[i].state_in = 0;
	cmd[i].state_out = 0;
}

int	wrap_parse_pipe(t_cmd *s_cmd_line, char **cmd_line, int i, char **env)
{
	int	j;

	init_lst(s_cmd_line, i);
	cmd_line[i] = redir(cmd_line[i], &s_cmd_line[i]);
	if (!cmd_line[i])
		return (1);
	cmd_line[i] = pre_parse_quote(cmd_line[i], env);
	s_cmd_line[i].cmd = split(cmd_line[i], ' ');
	if (!s_cmd_line[i].cmd)
		return (1);
	j = -1;
	while (s_cmd_line[i].cmd[++j])
		s_cmd_line[i].cmd[j] = parse_quote(s_cmd_line[i].cmd[j], 1, env);
	return (0);
}

int	parse_pipe(t_cmd *s_cmd_line, char *str, char **env)
{
	int		i;
	char	**cmd_line;

	i = -1;
	if (!s_cmd_line)
		return (1);
	cmd_line = split(str, '|');
	if (!cmd_line)
		return (1);
	while (cmd_line && cmd_line[++i])
	{
		if (wrap_parse_pipe(s_cmd_line, cmd_line, i, env))
			return (1);
	}
	free_split(cmd_line);
	s_cmd_line[i].cmd = NULL;
	return (0);
}

t_cmd	*parser(char *str, char **env)
{
	t_cmd	*s_cmd_line;
	int		c_p;

	if (!str || !ft_strncmp("", str, 1) || is_onlyspace(str))
		return (NULL);
	c_p = count_pipe(str);
	if (c_p == -1)
	{
		s_cmd_line = gc_malloc(sizeof(t_cmd) * 2);
		if (no_pipe(s_cmd_line, str, env))
			return (NULL);
	}
	else if (c_p == -2 || check_pipe(str))
		return (NULL);
	else
	{
		s_cmd_line = gc_malloc(sizeof(t_cmd) * (c_p + 2));
		if (parse_pipe(s_cmd_line, str, env))
			return (NULL);
	}
	return (s_cmd_line);
}
