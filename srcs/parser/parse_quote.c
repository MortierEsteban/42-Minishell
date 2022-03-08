/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:39:45 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/03 20:25:09 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*parse_quote(char *str)
{
	int		i;
	int		j;
	int		quot;
	char	*new;

	if (!str)
		return (NULL);
	new = gc_malloc(sizeof(char) * ft_strlen(str) + 1);
	quot = 0;
	i = 0;
	j = 0;
	while (str && str[i])
	{
		// if (str[i] == '$')
		// 	i += echospecial(str, envp, i + 1);
		if (str[i] == '\'' && quot == 0)
			quot = 1;
		else if (str[i] == '\"' && quot == 0)
			quot = 2;
		else if ((str[i] == '\"' && quot == 2) || (str[i] == '\'' && quot == 1))
			quot = 0;
		else if ((str[i] == '\"' && quot == 1) || (str[i] == '\'' && quot == 2)
			|| (str[i] != '\"' && str[i] != '\''))
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[i] = 0;
	return (new);
}
