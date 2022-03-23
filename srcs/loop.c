/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/22 17:47:04 by lsidan           ###   ########.fr       */
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
	color = ft_strdup("");
	tmp = ft_strjoin(color, new);
	gc_free(new);
	gc_free(color);
	new = ft_strjoin(tmp, " ❯ ");
	new = ft_strjoin(new, "");
	return (new);
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

void	check_cmd(t_cmd *c_line, char ***env)
{
	if (c_line)
	{
		loop_lst(c_line, *env);
		pipex_process(c_line, env);
		free_cmd(c_line);
	}
	else
		ft_putstr_fd("Parse Error\n", 2);
}

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
			return (ft_exit_free(1, *env));
		else if (!nothing(line))
		{
			c_line = parser(line, *env);
			add_history(line);
			check_cmd(c_line, env);
		}
		free(line);
		gc_destroy();
	}
}
