/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:46:08 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/28 20:56:35 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	is_charset(char str, char *charset)
{
	while (*charset)
	{
		if (str == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	ft_wordlend(char *str, char *charset)
{
	int		i;
	char	c;

	i = -1;
	c = '\0';
	while (str[++i])
	{
		if (!c && (str[i] == '\'' || str[i] == '"'))
			c = str[i];
		else if (c == str[i])
			c = '\0';
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
	i = 0;
	c = '\0';
	skip_char(s, &i, charset);
	while (s[i])
	{
		if (!c && (s[i] == '\'' || s[i] == '\"'))
			c = s[i];
		else if (c == s[i])
			c = '\0';
		if (is_charset(s[i++], charset) && !c && ft_strlen(s + 1) > 0)
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

static char	*ft_strduppd(char *src, int len)
{
	char	*dst;
	int		i;

	i = -1;
	dst = gc_malloc((len + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (++i < len && src[i])
		dst[i] = src[i];
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
		len = ft_wordlend((char *)s, charset);
		splitted[i] = ft_strduppd((char *)s, len);
		if (!splitted[i])
			return (ft_malloc_error(splitted));
		s += len;
	}
	splitted[nb_w] = 0;
	return (splitted);
}
