/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsidan <lsidan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:38:44 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/22 10:56:06 by lsidan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// typedef struct s_token
// {
// 	int		type;
// 	char	*str;
// }	t_tok;

void	sh_loop(void);
int		echo(char *str, int fd, int flag);
int		pwd(int fd);
int		cd(const char *str);
int		export(char **env, int fd);
char	***parser(char *str);
void	ft_free_cmd(char **str);
int		count_pipe(char *str);
void	remove_n(char *str);
char	**get_env_var(char **env);

#endif