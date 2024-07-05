#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "string.h"

typedef struct s_token
{
	int		type;
	char	*data;
}			t_token;

typedef struct s_minishell
{
	char	*env;
	char	*line;
	char	**tokens;
	int		pipe_count;
	t_token	*tokenizer;
}			t_minishell;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"

void		parser(t_minishell *minishell);
int			quote_handler(t_minishell *minishell, int pipe_i, int sign);

#endif