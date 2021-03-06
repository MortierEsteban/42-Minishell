/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:32:21 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/22 16:18:27 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_n(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != 'n')
			return (1);
	return (0);
}

void	process_args(char **cmd, int *flag_n, int *i)
{
	int	_i;
	int	stop;

	_i = *i;
	stop = 0;
	while (cmd[_i] && cmd[_i][0] == '-' && \
		cmd[_i][1] == 'n' && !stop)
	{
		cmd[_i] = inter(cmd[_i], "-n");
		if (!ft_strcmp(cmd[_i], "-n"))
			*flag_n = 1;
		else
		{
			ft_putstr_fd(cmd[_i], STDOUT);
			ft_putchar_fd(' ', STDOUT);
			stop = 1;
		}
		_i++;
	}
	*i = _i;
}

int	ft_echo(char ***env, t_cmd cmd)
{
	int	i;
	int	flag;

	(void) env;
	i = 1;
	flag = 0;
	process_args(cmd.cmd, &flag, &i);
	while (cmd.cmd[i])
	{
		ft_putstr_fd(cmd.cmd[i], STDOUT);
		if (cmd.cmd[i + 1])
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (flag != 1)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}

void	wrap_inter(char *s, int i, char **new, int *tab)
{
	if (!tab[(unsigned char) s[i]])
	{
		if (!*new)
			*new = strdup_pimp(&s[i], 1);
		else
			*new = ft_strljoin(*new, &s[i], 1);
		tab[(unsigned char) s[i]] = 1;
	}
}

char	*inter(char *s1, char *s2)
{
	int		i;
	char	*new;
	int		table[255];

	i = -1;
	while (++i < 255)
		table[i] = 0;
	i = -1;
	new = NULL;
	while (s1[++i])
		wrap_inter(s1, i, &new, table);
	i = -1;
	while (s2[++i])
		wrap_inter(s2, i, &new, table);
	if (!new || check_n(new + 1))
	{
		gc_free(new);
		return (s1);
	}
	gc_free(s1);
	return (new);
}
