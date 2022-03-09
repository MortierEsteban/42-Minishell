/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:38:44 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/09 14:33:27 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include "../libft/libft.h"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

//STATE_OUT = 1 -> '>'
//STATE_OUT = 2 -> '>>'
//STATE_IN = 1 -> '<'
//STATE_IN = ? -> '<<'

typedef struct s_cmd
{
	char	**cmd;
	int		state_in;
	t_list	*input;
	t_list	*h_doc;
	int		state_out;
	t_list	*output;
}	t_cmd;

//ENV VAR
char	***create_var_tab(char **env);

// SPLIT
char	**split(char const *s, char c);
char	*strdup_pimp(char *str, int len);
int		w_len(char *str, char *charset);
int		is_charset(char c, char *charset);
void	skip_char(char *s, int *i, char *charset);

// LOOP
void	sh_loop(char **env);

//BUILT-IN
int		echo(char *str);
int		pwd(int fd);
int		cd(const char *str);
int		export(char **env, int fd);

//PARSING
t_cmd	*parser(char *str);
void	join_args(t_cmd *s_cmd_line);
char	*process_join_arg(t_cmd *cmd, int i, int j, char *txt);
char	*parse_quote(char *str);
void	init_lst(t_cmd *cmd, int i);

//REDIR
char	*redir(char *str, t_cmd *cmd);
void	which_case(t_cmd *cmd, char *tmp, char c, char *d);
void	wrap_redir(char *str, char **new, t_cmd *cmd, int *k);
char	*redir(char *str, t_cmd *cmd);
int		len_filename(char *str, int i);
int		cpy_str(char *str, char **new, int *i);

//UTILS
char	**ft_malloc_error(char **tab);
char	**get_path(void);
char	*get_env_var(char *var);
int		count_pipe(char *str);
int		remove_n(char *str);
void	free_cmd(t_cmd	*c_line);
int		is_onlyspace(char *str);

//PIPEX
void	pipes_error(void);
int		nb_cmds(t_cmd *args);
char	*ft_check_path(char **args);
void	ft_exec(char **args, char **env, int diff);
int		pipex_process(t_cmd *args, char **env);
void	ft_pipex_dup(int i, t_cmd *args, int memory[2], int *pipe_exit);

//REDIR
int		*redir_handler(t_cmd cmd, int *pipe_exit);
int		*ft_redirects(t_cmd args);
void	ft_touch_files(char *filename);
#endif