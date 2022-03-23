/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/23 09:27:10 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**env_cpy;

	(void) ac;
	(void) av;
	env_cpy = ft_envcpy(env, 1);
	sh_loop(&env_cpy);
	usleep(20);
	gc_destroy();
	ft_exit_free(1, env_cpy);
	return (0);
}
