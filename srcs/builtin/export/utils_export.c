/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:45:28 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/16 14:19:05 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

char	**ft_recreate_env(void)
{
	char	**new;
	char	*pwd;

	new = malloc (sizeof(char *) * 1);
	if (!new)
		return (NULL);
	new[0] = NULL;
	ft_add_env (&new, "OLDPWD");
	ft_add_env (&new, "SHLVL=1");
	pwd = getcwd((char *) NULL, 0);
	pwd = ft_strjoin("PWD=", pwd);
	ft_add_env (&new, pwd);
	return (new);
}

void	ft_shlvl(char ***env)
{
	char	*strnb;
	int		pos;
	int		nb;

	strnb = ft_get_var_str(env, "SHLVL");
	nb = ft_atoi(strnb);
	nb = nb + 1;
	pos = ft_find_var(*env, "SHLVL");
	strnb = ft_strjoin("SHLVL=", ft_itoa(nb));
	free((*env)[pos]);
	(*env)[pos] = ft_strdup_nogc(strnb);
}
