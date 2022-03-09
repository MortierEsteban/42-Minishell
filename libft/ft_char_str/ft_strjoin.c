/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:25:12 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 17:26:26 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	j = 0;
	new = (char *) gc_malloc((len * sizeof(char) + 1));
	if (new == NULL)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	gc_free((void *)s1);
	return (new);
}

char	*ft_strljoin(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	j = 0;
	new = (char *) gc_malloc((len * sizeof(char) + 1));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j] && j < n)
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	gc_free((void *)s1);
	return (new);
}
