/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/24 16:29:06 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*parse_home_path(char *path, char **env)
{
	char	*home_path;
	char	*new;
	char	*tmp;
	char	*color;

	if (!path)
		return (NULL);
	home_path = ft_get_var_str(&env, "HOME");
	if (ft_strlen(path) < ft_strlen(home_path))
			new = path;
	else
		new = ft_strjoin("~", path + ft_strlen(home_path));
	color = ft_strdup(COLOR);
	tmp = ft_strjoin(color, new);
	gc_free(new);
	gc_free(color);
	new = ft_strjoin(tmp, " ❯ ");
	new = ft_strjoin(new, END_COLOR);
	return (new);
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
		ft_putstr_fd("Syntaxe Error\n", 2);
}

void	wrap_loop(t_cmd *c_line, char ***env, char *line)
{
	if (!nothing(line))
	{
		c_line = parser(line, *env);
		add_history(line);
		check_cmd(c_line, env);
	}
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
		prompt = parse_home_path(tmp, *env);
		free(tmp);
		line = readline(prompt);
		gc_free(prompt);
		if (!line)
			return (ft_exit_free(1, *env));
		wrap_loop(c_line, env, line);
		free(line);
		gc_destroy();
	}
}
