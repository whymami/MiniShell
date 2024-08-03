/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:56:37 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/03 13:36:02 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dlist.h"
# include "fcntl.h"
# include "libft.h"
# include "signal.h"
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define STD_INPUT 0
# define STD_OUTPUT 1

extern int	g_sig;
typedef struct s_fd
{
	int		change;
	int		std_in;
	int		std_out;
}			t_fd;

typedef struct s_minishell
{
	t_dlist	*env;
	char	*oldpwd;
	char	*line;
	int		pipe_count;
	int		*pipe_fd;
	int		*pid;
	int		hrd_count;
	int		sign;
	char	*path;
	char	***args;
	int		*heredoc_fd;
	char	***args_with_quotes;
	t_dlist	*tokens;
	t_dlist	*hrd_cmd;
	t_fd	g_fd;
	int		in_heredoc;
	int		exit_code;
	int		status;
}			t_minishell;

# define SUCCESS 0
# define FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token "

int			parser(t_minishell *minishell);
int			check_quote(char *line, int value_i);
int			pass_space(char *line, int *i);
void		lexer(t_minishell *minishell);
void		parse_env(t_minishell *minishell, char **env);
void		export(t_minishell *minishell, char **env_data_list, int *i);
void		print_env(t_minishell *minishell);
t_dlist		*search_env(t_minishell *minishell, char *key);
char		*get_pwd(void);
void		del(void *content);
void		unset(t_minishell *mini, char **key);
void		echo(char **args);
int			cd(t_minishell *mini, char *av);
int			execute_command(t_minishell *minishell);
char		*get_value(char *line);
void		ft_exit(t_minishell *mini, char **av);
int			cpy_arg(t_minishell *minishell);
int			check_builtin(t_minishell *minishell, char **cmd, char ***args,
				int *i);
int			create_fork(t_minishell *minishell, char **cmd, char ***args,
				int *i);
int			multiple_command(t_minishell *minishell);
char		**env(t_minishell *minishell);
char		*find_path(t_minishell *minishell, char *cmd);
void		signal_handler(int signo);
int			heredoc(t_minishell *mini);
int			check_direct(t_minishell *minishell, char **args);
void		dollar(t_minishell *mini, int i);
char		**ft_mini_split(const char *s, char c);
int			get_key(char *line);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin_char(char *s1, char c);
void		remove_quotes(char ***args);
int			replace_arg(char **args);
char		**my_realloc(char **ptr, size_t size);
int			type_control(t_minishell *minishell, char ***args, char **envs,
				int *i);
int			err_msg(char *cmd, char *arg, char *msg);
void		reset_fd(t_minishell *minishell);
void		remove_quotes(char ***args);
void		check_pid(pid_t *pid, t_minishell *minishell, char ***args, int *i);
void		free_args(char ***args);
void		free_split(char **split);
int			is_valid_env_char(char c);
void		get_ext_code(int *i, t_minishell *mini, char **result);
void		get_env(int *i, t_minishell *mini, char **str, char **result);
char		**get_delimiters(t_minishell *mini, char **args);
void		null_heredoc_args(char **args);
char		**merge_delimiters(char **delimiters, char **temp_delimiters);
int			create_pipe(t_minishell *minishell);
void		handle_pipe_dup(t_minishell *minishell, int i);
void		pipe_fork(t_minishell *minishell, int i, char **cmd, char ***args);
char		*handle_quotes(const char *str);
void		free_n_null(char **args, int *j);
void		dup_fd(t_minishell *mini);
void		free_n_null(char **args, int *j);
int			close_fd(t_minishell *minishell);
void		handle_signals(void);
int			check_syntax_errors(char **args);
#endif