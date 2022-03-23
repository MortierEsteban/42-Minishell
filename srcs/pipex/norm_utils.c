/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:00:18 by emortier          #+#    #+#             */
/*   Updated: 2022/03/23 15:13:30 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_norm_pdup(int *redir[2], int memory[2], int pipes[2], int diff)
{
	if ((*redir)[1] == -1)
	{
		if (diff != 0)
			(*redir)[1] = pipes[1];
		else
			(*redir)[1] = memory[1];
	}
}
