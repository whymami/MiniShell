#ifndef MINISHELL_H
# define MINISHELL_H

# include "dlink_list.h"
# include "ft_printf.h"
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "stdlib.h"
# include "string.h"

# define TRUE 1
# define FALSE 0

typedef struct s_token
{
	char			*command;
	char			**args;
	bool			meta_char;
}					t_token;

typedef struct s_minishell
{
	char			*env;
	char			*line;
	int				pipe_count;
	t_dlist	*tokens;
}					t_minishell;

# define SUCCESS 0
# define FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"

int					parser(t_minishell *minishell);
int					quote_handler(t_minishell *minishell, int pipe_i, int sign);
void				lexer(t_minishell *minishell);

#endif
