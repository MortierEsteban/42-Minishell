/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:33:39 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/22 10:34:06 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_free_cmd(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	count_pipe(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			j++;
	}
	if (!j)
		return (-1);
	return (j);
}

void	remove_n(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return ;
		}
	}
}
