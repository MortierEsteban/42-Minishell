/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:07:29 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/21 16:33:48 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	cpy_str(char *str, char **new, int *i)
{
	char	c;

	if (!*new && str[*i] != '<' && str[*i] != '>')
		*new = strdup_pimp(str + *i, 1);
	else if (str[*i] != '<' && str[*i] != '>')
		*new = ft_strljoin(*new, &str[*i], 1);
	if (str[*i] == '"' || str[*i] == '\'')
	{
		c = str[*i];
		*i += 1;
		while (str && str[*i] && str[*i] != c)
		{	
			*new = ft_strljoin(*new, &str[*i], 1);
			*i += 1;
		}
		*new = ft_strljoin(*new, &str[*i], 1);
		return (1);
	}
	return (0);
}

int	len_filename(char *str, int i)
{
	char	e;

	e = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			e = str[i++];
			while (str && str[i] && str[i] != e)
				i++;
		}
		else if (str[i] == '<' || str[i] == '>' || str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

int	wrap_redir(char *str, char **new, t_cmd *cmd, int *k)
{
	int		i;
	int		j;
	char	c;
	char	d;
	char	*tmp;

	i = *k;
	d = 0;
	if (!cpy_str(str, new, &i) && (str[i] == '<' || str[i] == '>'))
	{
		c = str[i++];
		if (str[i] == c)
			d = str[i++];
		while (ft_isspace(str[i]))
			i++;
		if (!str[i] || str[i] == '<' || str[i] == '>')
			return (1);
		j = len_filename(str, i);
		tmp = ft_strtrim(strdup_pimp(str + i, j - i), " ");
		if (which_case(cmd, tmp, c, d))
			return (1);
		i = --j;
	}
	*k = i;
	return (0);
}

char	*redir(char *str, t_cmd *cmd)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (wrap_redir(str, &new, cmd, &i))
			return (NULL);
		else
			i++;
	}
	if (new)
	{
		gc_free(str);
		return (new);
	}
	return (str);
}
