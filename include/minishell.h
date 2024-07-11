#ifndef MINISHELL_H
# define MINISHELL_H

# include "dlist.h"
# include "ft_printf.h"
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "stdlib.h"
# include "string.h"
# include <unistd.h>
# include "fcntl.h"

# define TRUE 1
# define FALSE 0

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
	char	*line;
	int		pipe_count;
	t_dlist	*tokens;
}			t_minishell;

# define SUCCESS 0
# define FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"

int			parser(t_minishell *minishell);
int			quote_handler(t_minishell *minishell, int pipe_i, int sign);
void		lexer(t_minishell *minishell);
void		parse_env(t_minishell *minishell, char **env);
void		export(t_minishell *minishell, char *env_data);
void		print_env(t_minishell *minishell);
t_dlist		*search_env(t_minishell *minishell, char *key);
void		get_pwd(void);
void		del(void *content);
void		unset(t_minishell *mini, char *key);

void execute_command(t_minishell *minishell);

#endif
