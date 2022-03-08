/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 08:37:32 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/02 15:38:49 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*strdup_pimp(char *str, int len)
{
	char	*dst;
	int		i;

	i = -1;
	dst = gc_malloc((len + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (++i < len && str[i])
		dst[i] = str[i];
	dst[i] = 0;
	return (dst);
}

int	w_len(char *str, char *charset)
{
	int		i;
	char	c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		if (!c && (str[i] == '\'' || str[i] == '"'))
			c = str[i];
		else if (c == str[i])
			c = 0;
		if (!c && is_charset(str[i], charset))
			return (i);
	}
	return (i);
}

void	skip_char(char *s, int *i, char *charset)
{
	int	j;

	j = *i;
	while (s && s[j] && s[j] == charset[0])
		j++;
	*i = j;
}

int	is_charset(char c, char *charset)
{
	if (c == charset[0])
		return (1);
	return (0);
}
