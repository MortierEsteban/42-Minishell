/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:37:46 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/15 15:15:27 by emortier         ###   ########.fr       */
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
	(void) 	ac;
	(void) 	av;
	char	**env_cpy;
	int		i;
	
	i = -1;
	env_cpy = ft_envcpy(env);
	sh_loop(&env_cpy);
	usleep(20);
	gc_destroy();
	return (0);
}
