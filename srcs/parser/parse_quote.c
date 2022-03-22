/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:39:45 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/22 08:52:09 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	s_machine_quote(int *quot, char *str, int i);

void	s_machine_quote(int *quot, char *str, int i)
{
	int	_q;

	_q = *quot;
	if (str[i] == '\'' && !_q)
		_q = 1;
	else if (str[i] == '\"' && !_q)
		_q = 2;
	else if ((str[i] == '\"' && _q == 2) || (str[i] == '\'' && _q == 1))
		_q = 0;
	*quot = _q;
}

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
		s_machine_quote(&quot, str, i);
		new = ft_strljoin(new, &str[i], 1);
		i++;
	}
	gc_free(str);
	return (new);
}

char	*get_env_name(char *str, int *j)
{
	int		_j;
	char	*tmp;

	tmp = NULL;
	_j = *j;
	while (str && str[_j] && stop(str[_j], TABLE))
	{
		if (!tmp)
			tmp = ft_strdup("");
		else
			tmp = ft_strljoin(tmp, &str[_j], 1);
		_j++;
	}
	*j = _j;
	return (tmp);
}

int	shinra_tensei(char *str, int quot, int *i, char **new)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	if (str[*i] == '$' && (quot == 0 || quot == 2))
	{
		if (str[*i + 1] == ' ' || !str[*i + 1])
			return (0);
		if (str[*i + 1] == '?')
		{
			tmp = ft_itoa(g_ex_status);
			*new = ft_strjoin(*new, tmp);
			gc_free(tmp);
			*i += 2;
			return (1);
		}
		tmp = get_env_name(str, i);
		tmp2 = getenv(tmp);
		if (tmp2)
			*new = ft_strjoin(*new, tmp2);
		gc_free(tmp);
		gc_free(tmp2);
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
		{
			new = ft_strjoin(new, getenv("HOME"));
			i++;
			continue ;
		}
		else if (p_s && shinra_tensei(str, quot, &i, &new))
			continue ;
		s_machine_quote(&quot, str, i);
		process_parse(str, &new, i, quot);
		i++;
	}
	gc_free(str);
	return (new);
}
