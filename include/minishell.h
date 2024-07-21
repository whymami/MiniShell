/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:56:37 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/21 00:34:35 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dlist.h"
# include "fcntl.h"
# include "ft_printf.h"
# include "stdlib.h"
# include "string.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>


# define TRUE 1
# define FALSE 0
# define STD_INPUT 0
# define STD_OUTPUT 1

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
	t_dlist	*tokens;
	t_dlist	*hrd_cmd;
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
void		export(t_minishell *minishell, char **env_data_list);
void		print_env(t_minishell *minishell);
t_dlist		*search_env(t_minishell *minishell, char *key);
char		*get_pwd(void);
void		del(void *content);
void		unset(t_minishell *mini, char **key);
void		echo(char **args);
int			cd(t_minishell *mini, char *av);
int			execute_command(t_minishell *minishell);
char		*get_value(char *line);
void		ft_exit(t_minishell *mini, char *av);
int			cpy_arg(t_minishell *minishell, char ***cmd, char ****args);
int			check_bultin(t_minishell *minishell, char **cmd, char ***args,
				int *i);
int			create_fork(t_minishell *minishell, char **cmd, char ***args,
				int *i);
int			multiple_command(t_minishell *minishell);
char		**env(t_minishell *minishell);
char		*find_path(t_minishell *minishell, char *cmd);
void		signal_handler(int signo);
int			heredoc(t_minishell *mini);
int			check_direct(t_minishell *minishell, char ***args);
void		dollar(t_minishell *mini, char **str);
char		**ft_mini_split(const char *s, char c);
int			get_key(char *line);
int			ft_strcmp(char *s1, char *s2);
#endif