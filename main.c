/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/17 11:23:28 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

void	ft_ctrlc(int sig)
{
	char	*tmp;
	char	*prompt;

	(void)sig;
	tmp = getcwd((char *) NULL, 0);
	prompt = parse_home_path(tmp);
	free(tmp);
	prompt = ft_strjoin("\n", prompt);
	ft_putstr_fd (prompt, 1);
}

void	ft_insane(int	sig)
{
	(void) sig;
	ft_putstr_fd("\b\b", 1);
}

int	main(int ac, char **av, char **env)
{
	char	**env_cpy;

	(void) ac;
	(void) av;
	(void) env;
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_insane);
	env_cpy = ft_envcpy(env, 1);
	sh_loop(&env_cpy);
	usleep(20);
	gc_destroy();
	return (0);
}
