/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/18 14:17:34 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_lst(t_list *head)
{
	t_list	*current;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		gc_free(current->content);
		current = current->next;
	}		
}

void	free_cmd(t_cmd	*c_line)
{
	int	i;
	int	j;

	i = -1;
	if (!c_line)
		return ;
	while (c_line[++i].cmd)
	{
		j = -1;
		while (c_line[i].cmd[++j])
			gc_free(c_line[i].cmd[j]);
		c_line[i].state_in = 0;
		c_line[i].state_out = 0;
		free_lst(c_line[i].h_doc);
		free_lst(c_line[i].input);
		free_lst(c_line[i].output);
		gc_free(c_line[i].cmd);
	}
	gc_free(c_line);
}

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

// void	print_debug(t_cmd *c_line, int i)
// {
// 	int	j;

// 	j = 0;
// 	dprintf(1, ">>>>>>>>> CMD %d : <<<<<<<<<\n", i);
// 	while (c_line && c_line[i].cmd && c_line[i].cmd[j])
// 		dprintf(1, "SPLITTED = %s\n", c_line[i].cmd[j++]);
// 	j = 0;
// 	dprintf(1, ">>>>>>>>> INPUT %d : <<<<<<<<<\n", i);
// 	print(c_line[i].input);
// 	dprintf(1, ">>>>>>>>> OUTPUT %d : <<<<<<<<<\n", i);
// 	print(c_line[i].output);
// 	dprintf(1, ">>>>>>>>> H_DOC %d : <<<<<<<<<\n", i);
// 	print(c_line[i].h_doc);
// }

void	sh_loop(char ***env)
{
	char	*line;
	char	*prompt;
	char	*tmp;
	t_cmd	*c_line;
	int		i;

	i = -1;
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
		{
			ft_putstr_fd("exit", 2);
			return (free(line));
		}
		else
			c_line = parser(line);
		add_history(line);
		if (c_line)
		{
			while (c_line && c_line[++i].cmd)
			{
				parse_list(c_line[i].input);
				parse_list(c_line[i].output);
				parse_list(c_line[i].h_doc);
				// print_debug(c_line, i);
			}
			i = -1;
			pipex_process(c_line, env);
			free_cmd(c_line);
		}
		else
			ft_putstr_fd("Parse Error\n", 2);
		free(line);
		gc_destroy();
	}
}
