/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:33:39 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 16:35:58 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	count_pipe(char *str)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	j = 0;
	while (str && str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			if (i == ft_strlen(str))
				return (-2);
			while (str && str[i] && str[i] != c \
					&& i <= ft_strlen(str))
				if (++i == ft_strlen(str))
					return (-2);
		}
		else if (str[i] == '|')
			j++;
	}
	if (!j)
		return (-1);
	return (j);
}

int	remove_n(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\n')
		{
			str[i] = 0;
			return (1);
		}
	}
	return (0);
}

char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = -1;
	while (tab[++i])
		gc_free(tab[i]);
	gc_free(tab);
	return (NULL);
}
