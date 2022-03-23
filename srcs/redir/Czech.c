/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Czech.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:52:48 by emortier          #+#    #+#             */
/*   Updated: 2022/03/23 16:47:19 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_redir_path(char *filename)
{
	int		i;
	int		j;
	char	*output;

	j = -1;
	i = -1;
	output = ft_strdup(filename);
	while (output[++i])
	{
		if (output[i] == '/')
			j = i;
	}
	if (j != -1)
	{
		output[j + 1] = '\0';
		return (output);
	}
	return (NULL);
}

char	*ft_error_path(char *filename)
{
	char	*tmp;

	tmp = ft_strdup("minishell: ");
	tmp = ft_strjoin(tmp, filename);
	tmp = ft_strjoin(tmp, ": No such file or directory\n");
	return (tmp);
}

int	ft_path_exists(t_list *output)
{
	char	*path;

	path = ft_redir_path(output->content);
	dprintf(2, "PATH = %s\n", path);
	if (!path)
	{
		output = output->next;
		return (0);
	}
	if (!ft_isadir(path))
	{
		gc_free(path);
		path = ft_error_path(output->content);
		ft_putstr_fd(path, 2);
		gc_free(path);
		return (1);
	}
	return (0);
}
