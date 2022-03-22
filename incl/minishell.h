/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:38:44 by lsidan            #+#    #+#             */
/*   Updated: 2022/03/22 10:42:07 by emortier         ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include "../libft/libft.h"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

//STATE_OUT = 1 -> '>'
//STATE_OUT = 2 -> '>>'
//STATE_IN = 1 -> '<'
//STATE_IN = 2 -> '<<'

# ifndef G_EX_STATUS
#  define G_EX_STATUS

extern unsigned char	g_ex_status;

# endif

# define TABLE "ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz0123456789_$!#?"

# define TABLE2 "ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz0123456789_"

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
int		ft_find_var(char **env, char *var);
void	ft_add_env(char ***env, char *newvar);
void	ft_remove_env(char ***env, int pos);
char	**ft_envcpy(char **env, int p_s);
char	**ft_sort_env(char **env);
char	**ft_resize_env(char **env, int nb);
char	*ft_get_var_str(char ***env, char *var);

// SPLIT
void	skip_char(char *s, int *i, char *charset);
char	**split(char const *s, char c);
char	*strdup_pimp(char *str, int len);
int		is_charset(char c, char *charset);
int		w_len(char *str, char *charset);
char	**free_split(char **tab);

// LOOP
void	sh_loop(char ***env);
char	*parse_home_path(char *path);

//SIG-HANDLER
void	ft_ctrlc(int sig);
void	ft_rm_sig_chars(int sig);
void	ft_exec_ctrlc(int sig);
void	ft_quit3(int sig);

//BUILT-IN
int		ft_cd(char ***env, t_cmd cmd);
int		ft_pwd(char ***env, t_cmd cmd);
int		ft_echo(char ***env, t_cmd cmd);
int		ft_export(char ***env, t_cmd cmd);
int		ft_bexit(char ***env, t_cmd cmd);
int		ft_env(char ***env, t_cmd cmd);
int		ft_unset(char ***env, t_cmd cmd );

//BUILT-IN-TRASH
void	ft_free_sorted(char **env);
char	*ft_strdup_nogc(char *s1);
char	**ft_add_quotes(char **sorted);
int		parse_env_name(char *varname);
void	ft_exit_free(int nb, char **env);
void	ft_shlvl(char ***env);
char	**ft_recreate_env(void);
void	ft_shlvl(char ***env);
char	*inter(char *s1, char *s2);

//PARSING
t_cmd	*parser(char *str);
void	join_args(t_cmd *s_cmd_line);
void	s_machine_quote(int *quot, char *str, int i);
void	init_lst(t_cmd *cmd, int i);
char	*process_join_arg(t_cmd *cmd, int i, int j, char *txt);
char	*pre_parse_quote(char *str);
char	*parse_quote(char *str, int p_s);
int		shinra_tensei(char *str, int quot, int *i, char **new);
void	process_parse(char *str, char **new, int i, int quot);
int		check_pipe(char *str);

//REDIR
int		which_case(t_cmd *cmd, char *tmp, char c, char d);
int		wrap_redir(char *str, char **new, t_cmd *cmd, int *k);
char	*redir(char *str, t_cmd *cmd);
char	*redir(char *str, t_cmd *cmd);
int		len_filename(char *str, int i);
int		cpy_str(char *str, char **new, int *i);

//UTILS
void	free_cmd(t_cmd	*c_line);
char	**ft_malloc_error(char **tab);
char	**get_path(void);
char	*get_env_var(char *var);
int		count_pipe(char *str);
void	ft_get_exit_stat(pid_t forks);
int		is_onlyspace(char *str);

//PIPEX
void	pipes_error(void);
void	ft_exec(char **args, char **env, int diff);
void	ft_pipex_dup(int i, t_cmd *args, int memory[2], int *pipe_exit);
char	*ft_check_path(char **args);
int		nb_cmds(t_cmd *args);
int		pipex_process(t_cmd *args, char ***env);
int		stop(char c, char *table);

//REDIR
void	ft_touch_files(char *filename);
int		*redir_handler(t_cmd cmd, int *pipe_exit, int memory[2]);
int		*ft_redirects(t_cmd args, int memory[2]);
#endif