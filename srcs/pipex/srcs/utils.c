/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:37:51 by emortier          #+#    #+#             */
/*   Updated: 2022/03/17 10:28:50 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	pipes_error(void)
{
	write (1, "There was an error while trying to use pipe.\n", 45);
}

int	nb_cmds(t_cmd *args)
{
	int	i;

	i = -1;
	while (args && args[++i].cmd)
	{
	}
	return (i);
}

int	ft_isadir(char *cmd)
{
	DIR	*dirname;

	dirname = opendir(cmd);
	if (dirname != NULL)
	{
		closedir(dirname);
		return (1);
	}
	else
		return (0);
	return (0);
}

char	*ft_here_type(char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd);
	if (!access(cmd, X_OK))
	{
		gc_free (tmp);
		return (cmd);
	}
	else if (!access(cmd, F_OK))
		tmp = ft_strjoin(tmp, ": cannot be executed\n");
	else if (ft_isadir(cmd))
		tmp = ft_strjoin(tmp, ": is a directory\n");
	else
		tmp = ft_strjoin(tmp, ": No such file or directory\n");
	ft_putstr_fd(tmp, 2);
	gc_free (tmp);
	return (NULL);
}

char	*ft_check_path(char **args)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	path = get_path();
	if (path == NULL)
		return (NULL);
	if (!ft_strncmp("./", args[0], 2))
		return (ft_here_type(args[0]));
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], args[0]);
	}
	i = -1;
	while (path[++i])
	{
		if (!access(path[i], F_OK | R_OK | X_OK))
			return (path[i]);
	}
	ft_putstr_fd("minishell: command not found\n", 2);
	return (NULL);
}
