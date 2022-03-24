/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:22:24 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/24 15:52:22 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_list	**gc_get_adrr(void)
{
	static t_list	*gcm;

	return (&gcm);
}

void	gc_destroy(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**gc_start;

	gc_start = gc_get_adrr();
	current = *gc_start;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*gc_start = 0;
}

void	*gc_malloc(unsigned long size)
{
	char	*buff;
	t_list	*new_elem;

	buff = malloc(size);
	if (!buff)
	{
		gc_destroy();
		return (0);
	}
	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
	{
		free(buff);
		gc_destroy();
		return (0);
	}
	new_elem->content = buff;
	new_elem->next = NULL;
	ft_lstadd_back(gc_get_adrr(), new_elem);
	return (buff);
}

int	gc_free(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**gc_start;

	prev = 0;
	gc_start = gc_get_adrr();
	current = *gc_start;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*gc_start = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
