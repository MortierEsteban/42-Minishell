/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/08 09:23:18 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

void	ft_ctrlc(int sig)
{
	(void)sig;
	printf("minishell>");
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	// export(env, STDOUT);
	sh_loop(env);
	signal(SIGINT, ft_ctrlc);
	// pwd(STDIN);
	// cd("../");
	// pwd(STDIN);
	// export(env, STDIN);
	// ft_free_cmd(path);
	usleep(20);
	gc_destroy();
	return (0);
}
