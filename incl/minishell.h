/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:38:44 by lsidan            #+#    #+#             */
/*   Updated: 2022/02/23 14:51:28 by emortier         ###   ########.fr       */
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
# include <string.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// typedef struct s_token
// {
// 	int		type;
// 	char	*str;
// }	t_tok;

void	sh_loop(char **env);
int		echo(char *str, int fd, int flag);
int		pwd(int fd);
int		cd(const char *str);
int		export(char **env, int fd);
char	***parser(char *str);
void	ft_free_cmd(char **str);
int		count_pipe(char *str);
void	remove_n(char *str);
char	**get_env_var(char **env);

//PIPEX//
int		pipex_process(char ***args, char **env);
int		nb_cmds(char **args);
void	ft_exec(char **args, char **env);
void	pipes_error(int *pipes[2], int i);
char	*ft_check_path(char **args, char **env);

#endif