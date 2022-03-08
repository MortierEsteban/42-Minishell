/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:46:18 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/07 20:44:17 by lsidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, int (*del)(void *))
{
	t_list	*t;

	if (!lst)
		return ;
	while (*lst)
	{
		t = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = t;
	}
}
