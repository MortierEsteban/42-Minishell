/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:54:19 by emortier          #+#    #+#             */
/*   Updated: 2022/03/15 16:15:00 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

char	*ft_strdup_nogc(char *s1)
{
	size_t		i;
	char		*s2;

	i = 0;
	s2 = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	else
	{
		while (s1[i])
		{
			s2[i] = s1[i];
			i++;
		}
	}
	s2[i] = '\0';
	return (s2);
}

void	ft_free_sorted(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		gc_free(env[i]);
	free (env);
}

char	**ft_resize_env(char **env, int nb)
{
	char	**remalloc;
	int		i;

	i = 0;
	while (env[i])
		i++;
	remalloc = malloc (sizeof(char *) * (i + 1 + nb));
	return (remalloc);
}
