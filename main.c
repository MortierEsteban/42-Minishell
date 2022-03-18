/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/18 11:02:11 by emortier         ###   ########.fr       */
=======
/*   Updated: 2022/03/17 18:55:06 by lsidan           ###   ########.fr       */
>>>>>>> f3c173a0d1321409b2147a718c20b8f2a3e61d86
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**env_cpy;

	(void) ac;
	(void) av;
<<<<<<< HEAD
=======
	(void) env;
>>>>>>> f3c173a0d1321409b2147a718c20b8f2a3e61d86
	env_cpy = ft_envcpy(env, 1);
	sh_loop(&env_cpy);
	usleep(20);
	gc_destroy();
	return (0);
}
