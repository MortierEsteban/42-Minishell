/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:39:45 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/25 09:52:41 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*pre_parse_quote(char *str, char **env)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_strdup("");
	i = 0;
	while (str && str[i])
	{
		if (shinra_tensei(str, &i, &new, env))
			continue ;
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
	_j++;
	while (str && str[_j] && stop(str[_j], TABLE))
	{
		if (!tmp)
			tmp = strdup_pimp(&str[_j], 1);
		else
			tmp = ft_strljoin(tmp, &str[_j], 1);
		_j++;
	}
	*j = _j;
	return (tmp);
}

int	dollar_ex_status(char *str, int *i, char **new)
{
	char	*tmp;

	if (str[*i + 1] == '?')
	{
		tmp = ft_itoa(g_ex_status);
		*new = ft_strjoin(*new, tmp);
		gc_free(tmp);
		*i += 2;
		return (1);
	}
	return (0);
}

int	shinra_tensei(char *str, int *i, char **new, char **env)
{
	char	*tmp;
	char	*tmp2;
	int		quot;

	tmp2 = NULL;
	quot = s_machine_quote(str, *i);
	if (str[*i] == '$' && (quot == 0 || quot == 2))
	{
		if (str[*i + 1] == ' ' || !str[*i + 1])
			return (0);
		if (dollar_ex_status(str, i, new))
			return (1);
		tmp = get_env_name(str, i);
		tmp2 = ft_get_var_str(&env, tmp);
		if (tmp2)
			*new = ft_strjoin(*new, tmp2);
		gc_free(tmp);
		gc_free(tmp2);
		return (1);
	}
	return (0);
}

char	*parse_quote(char *str, int p_s, char **env)
{
	int		i;
	int		quot;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_strdup("");
	i = 0;
	while (str && str[i])
	{
		quot = s_machine_quote(str, i);
		if (p_s && str[i] == '~' && quot == 0)
		{
			new = ft_strjoin(new, ft_get_var_str(&env, "HOME"));
			i++;
			continue ;
		}
		else if (p_s && shinra_tensei(str, &i, &new, env))
			continue ;
		process_parse(str, &new, i);
		i++;
	}
	gc_free(str);
	return (new);
}
