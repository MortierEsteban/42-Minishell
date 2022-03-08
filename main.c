/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/03 14:16:40 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	// export(env, STDOUT);
	sh_loop(env);
	// // usleep(20);
	gc_destroy();
	return (0);
}
