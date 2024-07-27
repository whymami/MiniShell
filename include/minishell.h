/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:56:37 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/27 08:47:07 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dlist.h"
# include "fcntl.h"
# include "ft_printf.h"
# include "libft.h"
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

typedef struct s_fd
{
	int		change;
	int		std_in;
	int		std_out;
}			t_fd;

typedef enum e_meta_type
{
	NONE,
	L_RED,
	R_RED,
	HEREDOC,
	DR_RED,
	DOLLAR,
}			t_meta_type;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_minishell
{
	t_dlist	*env;
	char	*oldpwd;
	char	*line;
	int		pipe_count;
	int		*pipe_fd;
	int		*pid;
	int		hrd_count;
	char	***args;
	char	***args_with_quotes;
	t_dlist	*tokens;
	t_dlist	*hrd_cmd;
	t_fd	g_fd;
	int		exit_code;
}			t_minishell;

# define SUCCESS 0
# define FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"

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
void		dollar(t_minishell *mini, char **str);
char		**ft_mini_split(const char *s, char c);
int			get_key(char *line);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin_char(char *s1, char c);
void		remove_quotes(char ***args);
void		replace_arg(char **args);
void		*my_realloc(void *ptr, size_t size);
int			get_exit_code(int status);
int			type_control(char ***args, char **envs, int *i);
#endif