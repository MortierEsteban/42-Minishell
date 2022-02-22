/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/22 11:08:17 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	main(int ac, char **av, char **env)
{
	int		i;
	// char	**path;

	(void) ac;
	(void) av;
	(void) env;
	i = -1;
	// path = get_env_var(env);
	// while (path && path[++i])
	// 	dprintf(1, "%s\n", path[i]);
	sh_loop();
	// pwd(STDIN);
	// cd("../");
	// pwd(STDIN);
	// export(env, STDIN);
	// ft_free_cmd(path);
	return (0);
}
