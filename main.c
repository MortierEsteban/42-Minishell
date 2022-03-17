/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/17 16:28:13 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"


int	main(int ac, char **av, char **env)
{
	char	**env_cpy;

	(void) ac;
	(void) av;
	(void) env;

	env_cpy = ft_envcpy(env, 1);
	sh_loop(&env_cpy);
	usleep(20);
	gc_destroy();
	return (0);
}
