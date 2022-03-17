/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:32:21 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/17 10:19:49 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*inter(char *s1, char *s2);

int	echo(char **cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i] && cmd[i][0] == '-')
	{
		cmd[i] = inter(cmd[i], "-n");
		if (!ft_strcmp(cmd[i], "-n"))
		{
			dprintf(1, "cc");
			flag = 1;
		}
		else
		{
			ft_putstr_fd(cmd[i], STDOUT);
			ft_putchar_fd(' ', STDOUT);
		}
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT);
		ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}

void	wrap_inter(char *s1, int i, char **new)
{
	if (!new)
		*new = strdup_pimp(&s1[i], 1);
	else
		*new = ft_strljoin(*new, &s1[i], 1);
}

char	*inter(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;
	int		table[255];

	i = -1;
	while (++i < 255)
		table[i] = 0;
	i = -1;
	new = NULL;
	while (s1[++i])
	{
		j = -1;
		while (s2[++j])
		{
			if (s1[i] == s2[j] && table[(unsigned char) s1[i]] != 1)
			{
				wrap_inter(s1, i, &new);
				table[(unsigned char) s1[i]] = 1;
			}
		}
	}
	if (!new || !ft_strcmp(new, "-"))
		return (s1);
	return (new);
}
