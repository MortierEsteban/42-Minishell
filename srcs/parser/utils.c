/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:33:39 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/28 20:47:30 by lsidan           ###   ########.fr       */
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
	while (str && str[++i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str && str[i] != '"' && i <= ft_strlen(str))
			{
				if (i == ft_strlen(str))
					return (-2);
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str && str[i] != '\'' && i <= ft_strlen(str))
			{
				if (i == ft_strlen(str))
					return (-3);
				i++;
			}
		}
		else if (str[i] == '|')
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

char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = -1;
	while (tab[++i])
		gc_free(tab[i]);
	gc_free(tab);
	return (NULL);
}
