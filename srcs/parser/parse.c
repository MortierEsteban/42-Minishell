/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:18:37 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/08 11:08:03 by lsidan           ###   ########lyon.fr   */
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
	s_cmd_line[0].input = NULL;
	s_cmd_line[0].apppend = NULL;
	s_cmd_line[0].h_doc = NULL;
	s_cmd_line[0].output = NULL;
	str = redir(str, &s_cmd_line[0]);
	s_cmd_line[0].cmd = split(str, ' ');
	if (!s_cmd_line)
		return ;
	while (s_cmd_line[0].cmd[++j])
		s_cmd_line[0].cmd[j] = parse_quote(s_cmd_line[0].cmd[j]);
	s_cmd_line[1].cmd = NULL;
}

char	*redir(char *str, t_cmd *cmd)
{
	int		i;
	int		j;
	t_list	*l_tmp;
	char	*new;
	char	*tmp;
	char	c;
	char	d;

	i = 0;
	c = 0;
	d = 0;
	dprintf(1, "OLD = |%s|\n", str);
	new = NULL;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str && str[i] && str[i] != c)
				i++;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (!new)
				new = strdup_pimp(str, i);
			c = str[i++];
			dprintf(1, "== %c ==\n", c);
			if (str[i] == c)
			{
				i++;
				d = str[i];
			}
			j = i;
			while (str && str[j])
			{
				if (str[j] == '<' || str[j] == '>')
					break ;
				j++;
			}
			tmp = ft_strtrim(strdup_pimp(str + i, j - i), " ");
			dprintf(1, "J = %d\nTMP = %s\n", j, tmp);
			if (c == '<' && !d)
			{
				if (!cmd->input)
				{
					dprintf(1, "INPUT : %s\n", tmp);
					cmd->input = ft_lstnew((void *) tmp);
				}
				else
				{
					cmd->state_in = 1;
					dprintf(1, "INPUT : %s\n", tmp);
					l_tmp = ft_lstlast(cmd->input);
					ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
				}
			}
			else if (c == '<' && d)
			{
				if (!cmd->h_doc)
				{
					dprintf(1, "H_DOC : %s\n", tmp);
					cmd->h_doc = ft_lstnew((void *) tmp);
				}
				else
				{
					dprintf(1, "H_DOC : %s\n", tmp);
					l_tmp = ft_lstlast(cmd->h_doc);
					ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
				}
			}
			else if (c == '>' && !d)
			{
				if (!cmd->output)
				{
					dprintf(1, "OUTPUT : %s\n", tmp);
					cmd->output = ft_lstnew((void *) tmp);
				}
				else
				{
					cmd->state_out = 1;
					dprintf(1, "OUTPUT : %s\n", tmp);
					l_tmp = ft_lstlast(cmd->output);
					ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
				}
			}
			else if (c == '>' && d)
			{
				if (!cmd->apppend)
				{
					dprintf(1, "APPEND : %s\n", tmp);
					cmd->apppend = ft_lstnew((void *) tmp);
				}
				else
				{
					cmd->state_out = 2;
					dprintf(1, "APPEND : %s\n", tmp);
					l_tmp = ft_lstlast(cmd->apppend);
					ft_lstadd_back(&l_tmp, ft_lstnew((void *) tmp));
				}
			}
			d = 0;
			i = --j;
		}
		i++;
	}
	if (new)
		return (new);
	return (str);
}

void	parse_pipe(t_cmd *s_cmd_line, char *str)
{
	int		i;
	int		j;
	char	**cmd_line;

	i = -1;
	if (!s_cmd_line)
	{
		dprintf(1, "Oops something went wrong.\n");
		return ;
	}
	cmd_line = split(str, '|');
	if (!cmd_line)
		return ;
	i = 0;
	while (cmd_line && cmd_line[i])
	{
		s_cmd_line[i].input = NULL;
		s_cmd_line[i].apppend = NULL;
		s_cmd_line[i].h_doc = NULL;
		s_cmd_line[i].output = NULL;
		cmd_line[i] = redir(cmd_line[i], &s_cmd_line[i]);
		s_cmd_line[i].cmd = split(cmd_line[i], ' ');
		j = -1;
		while (s_cmd_line[i].cmd[++j])
			s_cmd_line[i].cmd[j] = parse_quote(s_cmd_line[i].cmd[j]);
		if (!s_cmd_line[i].cmd)
			return ;
		i++;
	}
	s_cmd_line[i].cmd = NULL;
}

char	***create_var_tab(char **env)
{
	int		i;
	char	***var;

	i = -1;
	while (env[++i])
		i++;
	var = gc_malloc(sizeof(char *) * (i + 2));
	var[i] = 0;
	i = -1;
	while (env[++i])
	{
		var[i] = ft_split(env[i], '=');
		dprintf(1, "%s\n", *var[i]);
	}
	return (var);
}

t_cmd	*parser(char *str)
{
	t_cmd	*s_cmd_line;
	int		c_p;

	if (!str || !ft_strncmp(" ", str, 1) || !ft_strncmp("", str, 1))
		return (NULL);
	c_p = count_pipe(str);
	remove_n(str);
	if (c_p == -1)
	{
		s_cmd_line = gc_malloc(sizeof(t_cmd) * 2);
		no_pipe(s_cmd_line, str);
	}
	else if (c_p == -2)
	{
		dprintf(1, "===\n/!\\ : Missing d_quotes\n===\n");
		return (NULL);
	}
	else if (c_p == -3)
	{
		dprintf(1, "===\n/!\\ : Missing s_quotes\n===\n");
		return (NULL);
	}
	else
	{
		s_cmd_line = gc_malloc(sizeof(t_cmd) * (c_p + 2));
		parse_pipe(s_cmd_line, str);
	}
	return (s_cmd_line);
}

void	echo_parser(t_cmd *s_cmd_line)
{
	int		i;
	int		j;
	char	*txt;

	txt = NULL;
	i = -1;
	j = -1;
	while (s_cmd_line && s_cmd_line[++i].cmd)
	{
		if (s_cmd_line[i].cmd[0] && s_cmd_line[i].cmd[1])
		{
			j = 0;
			txt = NULL;
			while (s_cmd_line[i].cmd[++j])
			{
				if (!txt)
				{
					txt = ft_strjoin(s_cmd_line[i].cmd[j], "");
					continue ;
				}
				txt = ft_strjoin(txt, " ");
				txt = ft_strjoin (txt, s_cmd_line[i].cmd[j]);
			}
			s_cmd_line[i].cmd[1] = ft_strdup(txt);
			s_cmd_line[i].cmd[2] = NULL;
			gc_free(txt);
		}
	}
}
