/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:39:45 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 11:56:03 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*parse_quote(char *str)
{
	int		i;
	int		quot;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_strdup("");
	quot = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && quot == 0)
			quot = 1;
		else if (str[i] == '\"' && quot == 0)
			quot = 2;
		else if ((str[i] == '\"' && quot == 2) || (str[i] == '\'' && quot == 1))
			quot = 0;
		else if ((str[i] == '\"' && quot == 1) || (str[i] == '\'' && quot == 2)
			|| (str[i] != '\"' && str[i] != '\''))
			new = ft_strljoin(new, &str[i], 1);
		i++;
	}
	return (new);
}
