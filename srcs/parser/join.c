/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:14:07 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 12:14:35 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	join_args(t_cmd *s_cmd_line)
{
	int		i;
	int		j;
	char	*txt;

	i = -1;
	while (s_cmd_line && s_cmd_line[++i].cmd)
	{
		if (s_cmd_line[i].cmd[0] && s_cmd_line[i].cmd[1])
		{
			j = 0;
			txt = NULL;
			while (s_cmd_line[i].cmd[++j])
				txt = process_join_arg(s_cmd_line, i, j, txt);
			s_cmd_line[i].cmd[1] = ft_strdup(txt);
			s_cmd_line[i].cmd[2] = NULL;
			gc_free(txt);
		}
	}
}

char	*process_join_arg(t_cmd *cmd, int i, int j, char *txt)
{
	if (!txt)
	{
		txt = ft_strjoin(cmd[i].cmd[j], "");
		return (txt);
	}
	txt = ft_strjoin(txt, " ");
	txt = ft_strjoin (txt, cmd[i].cmd[j]);
	return (txt);
}
