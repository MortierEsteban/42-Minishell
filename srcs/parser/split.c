/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:46:08 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/28 21:13:36 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	is_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
	{
		if (c == charset[i])
			return (1);
	}
	return (0);
}

static int	w_len(char *str, char *charset)
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

static void	skip_char(char *s, int *i, char *charset)
{
	int	j;

	j = *i;
	while (s[j] && s[j] == charset[0])
		j++;
	*i = j;
}

static int	count_w(char *s, char *charset)
{
	int		w;
	int		i;
	char	c;

	w = 0 ;
	i = -1;
	c = 0;
	skip_char(s, &i, charset);
	while (s[++i])
	{
		if (!c && (s[i] == '\'' || s[i] == '\"'))
			c = s[i];
		else if (c == s[i])
			c = 0;
		if (is_charset(s[i], charset) && !c && ft_strlen(s + 1) > 0)
		{
			w++;
			while (s[i] && s[i] == charset[0])
				i++;
			continue ;
		}
	}
	if (s[i - 1] != c)
		w++;
	return (w);
}

static char	*strdup_pimp(char *str, int len)
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

char	**split(char const *s, char c)
{
	char		**splitted;
	char		charset[2];
	int			nb_w;
	int			i;
	int			len;

	i = -1;
	charset[0] = c;
	charset[1] = '\0';
	nb_w = count_w((char *)s, charset);
	splitted = (char **) gc_malloc(sizeof(char *) * (nb_w + 1));
	if (!splitted)
		return (0);
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
