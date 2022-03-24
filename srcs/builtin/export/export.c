/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:54:19 by emortier          #+#    #+#             */
/*   Updated: 2022/03/24 16:24:01 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

char	*ft_needsquotes(char *sorted)
{
	char	**tmp;
	int		j;

	tmp = ft_split(sorted, '=');
	if (!tmp)
		return (NULL);
	free(sorted);
	sorted = ft_strjoin(tmp[0], "=\"");
	if (tmp[1])
		sorted = ft_strjoin(sorted, tmp[1]);
	sorted = ft_strjoin(sorted, "\"\n");
	j = 0;
	while (tmp[j])
		free (tmp[j++]);
	free (tmp);
	return (sorted);
}

char	**ft_add_quotes(char **sorted)
{
	int		i;
	char	*swp;

	i = -1;
	while (sorted[++i])
	{
		if (ft_strchr(sorted[i], '='))
			sorted[i] = ft_needsquotes(sorted[i]);
		else
		{
			swp = ft_strdup(sorted[i]);
			free (sorted[i]);
			sorted[i] = swp;
		}
	}
	return (sorted);
}

void	ft_add_env(char ***env, char *newvar)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = ft_resize_env(*env, 1);
	while ((*env)[++i])
	{
		new_env[i] = ft_strdup_nogc((*env)[i]);
		free((*env)[i]);
	}
	new_env[i] = ft_strdup_nogc(newvar);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

void	export_wargs(char ***env, t_cmd cmd)
{
	int		pos;
	int		i;
	char	*error;

	i = 0;
	while (cmd.cmd[++i])
	{
		if (parse_env_name(cmd.cmd[i]))
		{
			error = ft_strjoin("minishell: export: `", cmd.cmd[i]);
			error = ft_strjoin(error, "': not a valid identifier\n");
			ft_putstr_fd(error, 2);
			gc_free (error);
			continue ;
		}
		pos = ft_find_var(*env, cmd.cmd[i]);
		if (pos >= 0 && ft_strchr(cmd.cmd[i], '='))
		{
			free((*env)[pos]);
			(*env)[pos] = ft_strdup_nogc(cmd.cmd[i]);
		}
		else if (pos < 0)
			ft_add_env(env, cmd.cmd[i]);
	}
}

int	ft_export(char ***env, t_cmd cmd)
{
	char	**sorted;
	int		i;

	(void)cmd;
	sorted = NULL;
	if (cmd.cmd[1] == NULL)
	{
		i = 0;
		sorted = ft_sort_env(*env);
		while (sorted && sorted[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sorted[i], 1);
			if (!ft_strchr(sorted[i], '='))
				ft_putstr_fd("\n", 1);
			i++;
		}
		ft_free_sorted (sorted);
	}
	else
		export_wargs(env, cmd);
	return (0);
}
