/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:46:08 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/24 13:00:45 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	check_quote(char *s, char *c, int *i)
{
	int	j;

	j = *i;
	if (!*c && (s[j] == '\'' || s[j] == '\"'))
		*c = s[j];
	else if (*c == s[j])
		*c = 0;
	*i = j;
}

int	count_w(char *s, char *charset)
{
	int		w;
	int		i;
	char	c;

	w = 0;
	i = 0;
	c = 0;
	skip_char(s, &i, charset);
	while (s && i <= ft_strlen(s) && s[i])
	{
		check_quote(s, &c, &i);
		if (is_charset(s[i], charset) && !c && ft_strlen(s + 1) > 0)
		{
			w++;
			while (s[i] && s[i] == charset[0])
				i++;
			continue ;
		}
		i++;
	}
	if (i > 0 && s[i - 1] != charset[0])
		w++;
	return (w);
}

char	**wrap_split(int nb_w, char **splitted, const char *s, char *charset)
{
	int	i;
	int	len;

	i = -1;
	while (++i < nb_w)
	{
		while (is_charset((char)*s, charset))
			s++;
		len = w_len((char *)s, charset);
		splitted[i] = strdup_pimp((char *)s, len);
		if (!splitted[i])
			return (ft_malloc_error(splitted));
		s += len;
	}
	splitted[nb_w] = 0;
	return (splitted);
}

char	**split(char const *s, char c)
{
	char		**splitted;
	char		charset[2];
	int			nb_w;

	if (!s)
		return (NULL);
	charset[0] = c;
	charset[1] = '\0';
	nb_w = count_w((char *)s, charset);
	splitted = (char **) gc_malloc(sizeof(char *) * (nb_w + 1));
	if (!splitted)
		return (0);
	splitted = wrap_split(nb_w, splitted, s, charset);
	return (splitted);
}
