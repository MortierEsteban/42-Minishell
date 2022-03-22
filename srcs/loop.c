/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/22 08:59:33 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*parse_home_path(char *path)
{
	char	*home_path;
	char	*new;
	char	*tmp;
	char	*color;

	if (!path)
		return (NULL);
	home_path = getenv("HOME");
	if (!*(path + ft_strlen(home_path)))
		new = ft_strdup("~");
	else
		new = ft_strjoin("~", path + ft_strlen(home_path));
	color = ft_strdup("\033[0;36m");
	tmp = ft_strjoin(color, new);
	gc_free(new);
	gc_free(color);
	new = ft_strjoin(tmp, " ❯ ");
	new = ft_strjoin(new, "\033[0m");
	return (new);
}

void	parse_list(t_list *head)
{
	t_list	*current;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		current->content = parse_quote(current->content, 0);
		current = current->next;
	}	
}

void	loop_lst(t_cmd *c_line)
{
	int	i;

	i = -1;
	while (c_line && c_line[++i].cmd)
	{
		parse_list(c_line[i].input);
		parse_list(c_line[i].output);
		parse_list(c_line[i].h_doc);
	}	
}

void	check_cmd(t_cmd *c_line, char ***env)
{
	if (c_line)
	{
		loop_lst(c_line);
		pipex_process(c_line, env);
		free_cmd(c_line);
	}
	else
		ft_putstr_fd("Parse Error\n", 2);
}

void	sh_loop(char ***env)
{
	char	*line;
	char	*prompt;
	char	*tmp;
	t_cmd	*c_line;

	(void) env;
	c_line = NULL;
	while (1)
	{
		signal(SIGINT, ft_ctrlc);
		signal(SIGQUIT, ft_rm_sig_chars);
		tmp = getcwd((char *) NULL, 0);
		prompt = parse_home_path(tmp);
		free(tmp);
		line = readline(prompt);
		gc_free(prompt);
		if (!line)
			return (free(line));
		else
			c_line = parser(line);
		add_history(line);
		check_cmd(c_line, env);
		free(line);
		gc_destroy();
	}
}
