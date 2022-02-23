/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:18:37 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/23 14:55:23 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	no_pipe(char ***s_cmd_line, char *str)
{
	if (!s_cmd_line)
		return ;
	*s_cmd_line++ = ft_split(str, ' ');
	if (!*s_cmd_line)
		return ;
	*s_cmd_line = NULL;
}

void	parse_pipe(char ***s_cmd_line, char *str)
{
	int		i;
	char	**cmd_line;

	i = -1;
	if (!s_cmd_line)
		return ;
	cmd_line = ft_split(str, 3);
	if (!cmd_line)
		return ;
	while (cmd_line && cmd_line[++i])
		dprintf(1, "CMD SPLIT : %s\n", cmd_line[i]);
	i = 0;
	while (cmd_line && cmd_line[i])
	{
		s_cmd_line[i] = ft_split(cmd_line[i], ' ');
		if (!s_cmd_line[i])
			return ;
		i++;
	}
	s_cmd_line[i] = NULL;
}

char	***parser(char *str)
{
	char	***s_cmd_line;
	char	*txt;
	int		i;
	int		j;
	int		c_p;

	i = -1;
	j = 0;
	txt = NULL;
	c_p = count_pipe(str);
	if (!ft_strncmp("\n", str, 1))
		return (NULL);
	remove_n(str);
	dprintf(1, "STR = %s\nC_P = %d\n", str, c_p);
	if (c_p == -1)
	{
		s_cmd_line = gc_malloc(sizeof(char **) * 2);
		no_pipe(s_cmd_line, str);
	}
	else
	{
		s_cmd_line = gc_malloc(sizeof(char **) * (count_pipe(str) + 2));
		parse_pipe(s_cmd_line, str);
	}
	while (s_cmd_line && s_cmd_line[++i])
	{
		if (!ft_strcmp(s_cmd_line[i][0], "echo") && \
			!ft_strcmp(s_cmd_line[i][1], "-n"))
		{
			j = 1;
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
		else if (!ft_strcmp(s_cmd_line[i][0], "echo") && \
			ft_strcmp(s_cmd_line[i][1], "-n") != 0)
		{
			j = 0;
			txt = NULL;
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
			gc_free(s_cmd_line[i][j]);
			//attention
			s_cmd_line[i][1] = txt;
			s_cmd_line[i][2] = NULL;
			dprintf(1, "%s\n", txt);
		}
	}
	return (s_cmd_line);
}
