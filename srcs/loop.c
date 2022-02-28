/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/28 15:16:47 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	sh_loop(void)
{
	char	*line;
	char 	***c_line;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = 0;
	while (k != 3)
	{
		ft_putstr_fd("$> ", STDOUT);
		line = get_next_line(STDIN);
		c_line = parser(line);
		if (!c_line)
			return ;
		echo_parser(c_line);
		i = -1;
		while (c_line && c_line[++i])
		{
			j = -1;
			dprintf(1, ">>>>>>>>> cmd %d : <<<<<<<<<\n", i);
			while(c_line[i][++j])
				dprintf(1, "SPLITTED = %s\n", c_line[i][j]);
		}
		k++;
	}
}
 