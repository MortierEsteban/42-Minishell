/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:33:39 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/21 11:00:21 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_quote(char *str, int *i)
{
	int		_i;
	char	c;

	_i = *i;
	c = 0;
	if (str[_i] == '"' || str[_i] == '\'')
	{
		c = str[_i++];
		if (_i == ft_strlen(str))
		{
			return (1);
		}
		while (str && str[_i] && str[_i] != c \
				&& ++_i <= ft_strlen(str))
			if (_i == ft_strlen(str))
				return (1);
	}
	*i = _i;
	return (0);
}

void	gc_destroy_env(char	**env)
{
	static char	**save = NULL;
	int			i;

	if (env)
	{
		save = env;
		return ;
	}
	i = -1;
}

int	count_pipe(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str && str[++i])
	{
		if (check_quote(str, &i))
			return (-2);
		if (str[i] == '|')
		{
			while (ft_isspace(str[++i]))
			{
			}
			if (!str[i] || str[i--] == '|')
				return (-2);
			else
				j++;
		}
	}
	if (!j)
		return (-1);
	return (j);
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

int	stop(char c, char *table)
{
	int	i;

	i = -1;
	while (table[++i])
	{
		if (c == table[i])
			return (1);
	}
	return (0);
}
