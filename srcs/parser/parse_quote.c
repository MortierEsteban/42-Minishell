/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:39:45 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/08 11:21:28 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*parse_quote(char *str)
{
	int		i;
	int		j;
	int		quot;
	char	*new;
	char	tmp[100];
	char 	*env;
	int		len;

	if (!str)
		return (NULL);
	new = gc_malloc(sizeof(char) * ft_strlen(str) + 1);
	quot = 0;
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && (quot == 0 || quot == 2))
		{
			i++;
			while (str && str[i] && str[i] != ' ')
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
			tmp[j] = 0;
			env = getenv(tmp);
			len = ft_strlen(env);
			new = gc_malloc(sizeof(char) * (len + ft_strlen(str) + 1));
			ft_strlcat(new, env, len + 1);
			ft_strlcat(new + len, str + i, ft_strlen(str + i) + 1);
			dprintf(1, "== %s ==\n", new);
			j = 0;
		}
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
