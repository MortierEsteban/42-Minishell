/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 16:11:10 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/28 18:08:24 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char	*s1, const char	*s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || !s1 || !s2)
		return (0);
	while (s1 && s2 && (s1[i] || s2[i]) && i < n - 1 && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - s2[i]);
}

int	ft_strcmp(const char	*s1, const char	*s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - s2[i]);
}
