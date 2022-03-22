/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:03:12 by emortier          #+#    #+#             */
/*   Updated: 2022/03/21 13:42:33 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_ctrlc(int sig)
{
	char	*tmp;
	char	*prompt;

	(void) sig;
	rl_on_new_line();
	tmp = getcwd((char *) NULL, 0);
	prompt = parse_home_path(tmp);
	free(tmp);
	prompt = ft_strjoin(prompt, rl_line_buffer);
	prompt = ft_strjoin(prompt, "  \b\b\n");
	ft_putstr_fd(prompt, 2);
	g_ex_status = 1;
	gc_free(prompt);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_rm_sig_chars(int sig)
{
	char	c;

	(void) sig;
	rl_on_new_line();
	if (rl_point == ft_strlen(rl_line_buffer))
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \b\b", 4);
	}
	else if (rl_point == ft_strlen(rl_line_buffer) - 1)
	{
		rl_on_new_line();
		rl_redisplay();
		c = rl_line_buffer[rl_point];
		write(2, &c, 1);
		write(2, " \b\b", 3);
		rl_point++;
	}
	rl_redisplay();
}

void	ft_exec_ctrlc(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 2);
	g_ex_status = 130;
}

void	ft_quit3(int sig)
{
	(void) sig;
	ft_putstr_fd ("Quit: 3\n", 2);
	g_ex_status = 131;
}
