/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:34:01 by emortier          #+#    #+#             */
/*   Updated: 2022/03/17 11:10:26 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_nb_arg(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
	}
	return (i);
}

void	ft_exit_free(int nb, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	ft_putstr_fd("exit\n", 1);
	exit (nb);
}

int	ft_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[(*i)++] == '-')
			sign *= -1;
	}
	return (sign);
}

int	ft_atol_exit(char *str, char **env)
{
	int					i;
	unsigned long long	nb;
	unsigned long long	max;
	int					sign;

	i = 0;
	nb = 0;
	sign = ft_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	max = 9223372036854775807;
	if (str[i] == '\0' && \
	((nb <= max && sign == 1) || (nb <= max + 1 && sign == -1)))
		ft_exit_free(nb * sign, env);
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	return (-1);
}

int	ft_bexit(char **cmd, char **env)
{
	int	nb_args;

	nb_args = ft_nb_arg(cmd);
	if (nb_args > 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else if (nb_args == 1)
		exit(0);
	else
		ft_atol_exit(cmd[1], env);
	g_ex_status = 1;
	return (0);
}
