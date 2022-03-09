/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 11:37:17 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_cmd(t_cmd	*c_line)
{
	int	i;
	int	j;

	ft_lstclear(&c_line->input, gc_free);
	ft_lstclear(&c_line->apppend, gc_free);
	ft_lstclear(&c_line->h_doc, gc_free);
	ft_lstclear(&c_line->output, gc_free);
	i = -1;
	if (!c_line)
		return ;
	while (c_line[++i].cmd)
	{
		j = -1;
		while (c_line[i].cmd[++j])
			gc_free(c_line[i].cmd[j]);
		gc_free(c_line[i].cmd);
	}
	gc_free(c_line);
}

char	*parse_home_path(char *path)
{
	char	*home_path;
	char	*new;
	char	*color;

	if (!path)
		return (NULL);
	home_path = getenv("HOME");
	if (!*(path + ft_strlen(home_path)))
		new = ft_strdup("~");
	else
		new = ft_strjoin("~", path + ft_strlen(home_path));
	color = ft_strdup("\033[0;36m");
	new = ft_strjoin(color, new);
	new = ft_strjoin(new, " ❯ ");
	new = ft_strjoin(new, "\033[0m");
	return (new);
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

void	sh_loop(char **env)
{
	char	*line;
	char	*prompt;
	char	*tmp;
	t_cmd	*c_line;
	// int		i;
	// int		j;

	// i = 0;
	(void) env;
	c_line = NULL;
	while (1)
	{
		tmp = getcwd((char *) NULL, 0);
		prompt = parse_home_path(tmp);
		free(tmp);
		line = readline(prompt);
		add_history(line);
		if (!line || !ft_strcmp("exit", line))
			return (free(line));
		else
			c_line = parser(line);
		if (c_line)
		{
		// 	i = 0;
		// 	echo_parser(c_line);
		// 	while (c_line && c_line[i].cmd)
		// 	{
		// 		j = 0;
		// 		dprintf(1, ">>>>>>>>> CMD %d : <<<<<<<<<\n", i);
		// 		while (c_line && c_line[i].cmd && c_line[i].cmd[j])
		// 		{
		// 			dprintf(1, "SPLITTED = %s\n", c_line[i].cmd[j]);
		// 			j++;
		// 		}
		// 		dprintf(1, ">>>>>>>>> INPUT %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].input);
		// 		dprintf(1, ">>>>>>>>> OUTPUT %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].output);
		// 		dprintf(1, ">>>>>>>>> APPEND %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].apppend);
		// 		dprintf(1, ">>>>>>>>> H_DOC %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].h_doc);
		// 		i++;
		// 	}
			pipex_process(c_line, env);
			free_cmd(c_line);
		}
		free(line);
		gc_destroy();
	}
}

		// if (c_line)
		// {
		// 	i = 0;
		// 	while (c_line && c_line[i].cmd)
		// 	{
		// 		j = 0;
		// 		dprintf(1, ">>>>>>>>> CMD %d : <<<<<<<<<\n", i);
		// 		while (c_line && c_line[i].cmd && c_line[i].cmd[j])
		// 		{
		// 			dprintf(1, "SPLITTED = %s\n", c_line[i].cmd[j]);
		// 			j++;
		// 		}
		// 		dprintf(1, ">>>>>>>>> INPUT %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].input);
		// 		dprintf(1, ">>>>>>>>> OUTPUT %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].output);
		// 		dprintf(1, ">>>>>>>>> APPEND %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].apppend);
		// 		dprintf(1, ">>>>>>>>> H_DOC %d : <<<<<<<<<\n", i);
		// 		print(c_line[i].h_doc);
		// 		i++;
		// 	}