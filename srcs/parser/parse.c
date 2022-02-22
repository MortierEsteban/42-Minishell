/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:18:37 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/22 14:51:20 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	no_pipe(char ***s_cmd_line, char *str)
{
	if (!s_cmd_line)
		return ;
	s_cmd_line[0] = ft_split(str, ' ');
	if (!s_cmd_line[0])
		return ;
	s_cmd_line[1] = NULL;
}

void	parse_pipe(char ***s_cmd_line, char *str)
{
	int		i;
	char	**cmd_line;

	i = -1;
	if (!s_cmd_line)
		return ;
	cmd_line = ft_split(str, '|');
	if (!cmd_line)
		return ;
	while (cmd_line[++i])
		dprintf(1, "CMD SPLIT : %s\n", cmd_line[i]);
	i = -1;
	while (cmd_line[++i])
	{
		s_cmd_line[i] = ft_split(cmd_line[i], ' ');
		if (!s_cmd_line[i])
			return ;
	}
	ft_free_cmd(cmd_line);
	s_cmd_line[i] = NULL;
}

char	***parser(char *str)
{
	char	***s_cmd_line;
	char	*txt;
	int		i;
	int		j;

	i = -1;
	j = 0;
	txt = NULL;
	remove_n(str);
	dprintf(1, "STR = %s\nC_P = %d\n", str, count_pipe(str));
	if (count_pipe(str) == -1)
	{
		s_cmd_line = malloc(sizeof(char **) + 1);
		no_pipe(s_cmd_line, str);
	}
	else
	{
		s_cmd_line = (char ***) malloc(sizeof(char **) * count_pipe(str) + 1);
		parse_pipe(s_cmd_line, str);
	}
	while (s_cmd_line[++i])
	{
		j = 1;
		if (!ft_strcmp(s_cmd_line[i][0], "echo") && \
			!ft_strcmp(s_cmd_line[i][1], "-n"))
		{
			while (s_cmd_line[i][++j])
			{
				if (!txt)
				{
					txt = ft_strjoin(s_cmd_line[i][j], "");
					continue ;
				}
				txt = ft_strjoin(txt, " ");
				txt = ft_strjoin (txt, s_cmd_line[i][j]);
			}
			dprintf(1, "%s\n", txt);
		}
	}
	return (s_cmd_line);
}
