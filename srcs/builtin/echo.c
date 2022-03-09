/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:32:21 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 14:19:35 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_rewind(int i, char *arg)
{
	while (i > 0 && arg[i] != '-')
		i--;
		return (i);
}

char *ft_get_optns(char *arg)
{
	int		i;
	char	*optns;

	i = 0;
	while (arg[i] == '')
	if (arg[i] != '\0' && i - 1 > 0 && arg[i - 1] != ' ')
		i = ft_rewind(i, arg);
	optns = ft_substr(arg, 0, i);
	dprintf(2, "optns = %s\n", optns);
	return (optns);
}

char	*parse_n(char *arg)
{
	char *optns;

	optns = ft_get_optns(arg);
	return (arg);
}

int	echo(char *str)
{
	if (!str)
		return (1);
	parse_n(str);
	return (0);
}
