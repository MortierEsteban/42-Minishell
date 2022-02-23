/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:48:50 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/23 10:09:36 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *a)
{
	gc_free(a);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[MAX_FD][BUFFER_SIZE + 1];
	char		*txt;
	int			i;

	i = 1;
	txt = NULL;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (0);
	if (ft_search(buff[fd], '\n') != -1)
	{
		ft_cut(buff[fd]);
		txt = ft_join(txt, buff[fd]);
		if (txt[0] == '\0')
			txt = ft_free(txt);
	}
	while (ft_search(buff[fd], '\n') == -1 && i > 0)
	{
		i = read(fd, buff[fd], BUFFER_SIZE);
		if (i <= 0)
			return (txt);
		buff[fd][i] = '\0';
		txt = ft_join(txt, buff[fd]);
	}
	return (txt);
}
