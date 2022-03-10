/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/10 09:21:45 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

void	ft_ctrlc(int sig)
{
	(void)sig;
	printf("minishell>\n");
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	// signal(SIGINT, ft_ctrlc);
	sh_loop(env);
	usleep(20);
	gc_destroy();
	return (0);
}
