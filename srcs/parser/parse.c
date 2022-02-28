/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:18:37 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/28 14:52:43 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	no_pipe(char ***s_cmd_line, char *str)
{
	if (!s_cmd_line)
	{
		dprintf(1, "Oops something went wrong.\n");
		return ;
	}
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
	{
		dprintf(1, "Oops something went wrong.\n");
		return ;
	}
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
	i = 0;
	while (cmd_line && cmd_line[i])
		i++;
	s_cmd_line[i] = NULL;
}

char	***parser(char *str)
{
	char	***s_cmd_line;
	int		c_p;

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
		s_cmd_line = gc_malloc(sizeof(char **) * (c_p + 2));
		parse_pipe(s_cmd_line, str);
	}
	return (s_cmd_line);
}

int	check_redir(char *str)
{
	int	i;

	i = -1;
	dprintf(1, "%s\n", str);
	while (str[++i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				return (2);
			return (1);
		}
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				return (4);
			return (3);
		}
	}
	return (0);
}

void	echo_parser(char ***s_cmd_line)
{
	int		i;
	int		j;
	char	*txt;

	txt = NULL;
	i = -1;
	j = -1;
	while (s_cmd_line[++i])
	{
		while (s_cmd_line[i][++j])
		{
			if (check_redir(s_cmd_line[i][j]))
				return ;
		}
	}
	i = -1;
	while (s_cmd_line && s_cmd_line[++i])
	{
		if (!ft_strncmp(s_cmd_line[i][0], "echo", 4) && \
			!ft_strncmp(s_cmd_line[i][1], "-n", 2))
		{
			j = 1;
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
			s_cmd_line[i][2] = ft_strdup(txt);
			s_cmd_line[i][3] = NULL;
			gc_free(txt);
		}
		else if (!ft_strncmp(s_cmd_line[i][0], "echo", 4) && \
			ft_strncmp(s_cmd_line[i][1], "-n", 2) != 0)
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
			s_cmd_line[i][1] = ft_strdup(txt);
			s_cmd_line[i][2] = NULL;
			gc_free(txt);
		}
	}
}
