/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:32:21 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 15:50:44 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_rewind(int i, char *arg)
{
	while (i > 0 && arg[i] != '-')
		i--;
		return (i);
}

int ft_get_optns(char *arg)
{
	int		i;
	int		j;
	char	*optns;
	char	*tmp;

	i = 0;
	optns = ft_strdup("");
	while (arg[i])
	{
		j = i + 1;
		if (arg[i] == '-')
		{
			while (arg[j] == 'n')
				j++;
			if (arg[j] == ' ')
			{
				tmp = ft_substr(arg, i, j);
				dprintf(1, "tmp = |%s|\n", tmp);
				optns = ft_strjoin(optns, tmp);
			}
			else
				break ;
		}
		i = j;
	}
	dprintf(2, "optns = %s\n", optns);
	return (j);
}

char	*parse_n(char *arg)
{
	int optns;

	optns = ft_get_optns(arg);
	return (arg);
}

int	echo(char *str)
{
	dprintf(1, "args = |%s|\n", str);
	parse_n(str);
	return (0);
}
