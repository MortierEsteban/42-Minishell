/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:01:35 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/28 21:02:48 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_cmd(char ***c_line)
{
	int	i;
	int	j;

	i = -1;
	while (c_line[++i])
	{
		j = -1;
		while (c_line[i][++j])
			gc_free(c_line[i][j]);
		gc_free(c_line[i]);
	}
	gc_free(c_line);
}

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
	while (k != -1)
	{
		ft_putstr_fd("$> ", STDOUT);
		line = get_next_line(STDIN);
		if (!line)
			return ;
		if (!ft_strcmp("exit\n", line))
			return ;
		c_line = parser(line);
		if (c_line)
		{	
			echo_parser(c_line);
			i = -1;
			while (c_line && c_line[++i])
			{
				j = -1;
				dprintf(1, ">>>>>>>>> cmd %d : <<<<<<<<<\n", i);
				while(c_line[i][++j])
					dprintf(1, "SPLITTED = %s\n", c_line[i][j]);
			}
			free_cmd(c_line);
			gc_free(line);
		}
		k++;
	}
}
 