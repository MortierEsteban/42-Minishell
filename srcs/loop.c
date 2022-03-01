/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/01 15:35:16 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	sh_loop(char **env)
{
	char	*line;
	char 	***c_line;
	int		i;
	int		j;

	(void) env;
	i = -1;
	j = -1;	
	c_line = NULL;
	while (1)
	{
		usleep(60);
		ft_putstr_fd("$> ", STDOUT);
		line = get_next_line(STDIN);
		c_line = parser(line);
		i = -1;
		// while (c_line[++i])
		// {
		// 	j = 0;
		// 	dprintf(1, ">>>>>>>>> cmd %d : <<<<<<<<<\n", i);
		// 	while(c_line[i][j])
		// 		dprintf(1, "SPLITTED = %s\n", c_line[i][j++]);
		// }
		if (c_line)
		{
			pipex_process(c_line, env);
			// c_line = NULL;
			return;
		}
	}
	gc_destroy();
}
 