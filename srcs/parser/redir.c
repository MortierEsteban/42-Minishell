/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:07:29 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 20:26:44 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	cpy_str(char *str, char **new, int *i)
{
	char	c;

	if (!*new && str[*i] != '<' && str[*i] != '>')
		*new = strdup_pimp(str, 1);
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

void	wrap_redir(char *str, char **new, t_cmd *cmd, int *k)
{
	int		i;
	int		j;
	char	c;
	char	d;
	char	*tmp;

	i = *k;
	j = 0;
	d = 0;
	if (!cpy_str(str, new, &i) && (str[i] == '<' || str[i] == '>'))
	{
		c = str[i++];
		if (str[i] == c)
			d = str[i++];
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '<' || str[i] == '>')
			return (ft_putstr_fd("cassé", 2));
		j = len_filename(str, i);
		tmp = ft_strtrim(strdup_pimp(str + i, j - i), " ");
		which_case(cmd, tmp, c, &d);
		i = --j;
	}
	*k = i;
}

char	*redir(char *str, t_cmd *cmd)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (str[i])
	{
		wrap_redir(str, &new, cmd, &i);
		i++;
	}
	if (new)
		return (new);
	return (str);
}
