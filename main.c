/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/01 10:06:30 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	main(int ac, char **av, char **env)
{
	int		i;
	int		j;
	// char	***path;

	(void) ac;
	(void) av;
	(void) env;
	i = -1;
	j = -1;
	// path = create_var_tab(env);
	// while (path && path[++i])
	// {
	// 	j = -1;
	// 	while (path[i][++j])
	// 		dprintf(1, "%s\n", path[i][j]);
	// }
	sh_loop();
	// pwd(STDIN);
	// cd("../");
	// pwd(STDIN);
	// export(env, STDIN);
	// ft_free_cmd(path);
	usleep(20);
	gc_destroy();
	return (0);
}
