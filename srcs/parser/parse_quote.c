/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:39:45 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 20:46:59 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	shinra_tensei(char *str, int quot, int *i, char **new);

char	*pre_parse_quote(char *str)
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
		shinra_tensei(str, quot, &i, &new);
		if (str[i] == '\'' && quot == 0)
			quot = 1;
		else if (str[i] == '\"' && quot == 0)
			quot = 2;
		else if ((str[i] == '\"' && quot == 2) || (str[i] == '\'' && quot == 1))
			quot = 0;
		new = ft_strljoin(new, &str[i], 1);
		i++;
	}
	gc_free(str);
	return (new);
}

void	shinra_tensei(char *str, int quot, int *i, char **new)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (str[*i] == '$' && (quot == 0 || quot == 2))
	{
		j = *i;
		while (str && str[j] && str[j] != '/' && \
				str[j] != ' ' && str[j] != '"')
		{
			if (!tmp)
				tmp = ft_strdup("");
			else
				tmp = ft_strljoin(tmp, &str[j], 1);
			j++;
		}
		tmp2 = getenv(tmp);
		if (tmp2)
			*new = ft_strjoin(*new, tmp2);
		*i = j;
	}
}

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
		shinra_tensei(str, quot, &i, &new);
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
	gc_free(str);
	return (new);
}
