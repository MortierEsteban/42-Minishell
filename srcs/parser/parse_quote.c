/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:39:45 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/10 17:48:39 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
		if (shinra_tensei(str, quot, &i, &new))
			continue ;
		else if (str[i] == '\'' && quot == 0)
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

int	shinra_tensei(char *str, int quot, int *i, char **new)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	j = *i;
	if (str[j] == '$' && (quot == 0 || quot == 2))
	{
		if (str[j + 1] == '?')
			return (0 * dprintf(1, "EXIT VALUE :"));
		while (str && str[j] && str[j] != '/' && \
				str[j] != ' ' && str[j] != '"' && str[j] != '\'')
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
		gc_free(tmp);
		gc_free(tmp2);
		*i = j;
		return (1);
	}
	return (0);
}

char	*parse_quote(char *str, int p_s)
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
		if (p_s && str[i] == '~' && quot == 0)
			new = ft_strjoin(new, getenv("HOME"));
		else if (p_s && shinra_tensei(str, quot, &i, &new))
			continue ;
		else if (str[i] == '\'' && quot == 0)
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
