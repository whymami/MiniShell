#ifndef MINISHELL_H
# define MINISHELL_H


#include "readline/readline.h"
#include "readline/history.h"

#include "string.h"

typedef struct s_token
{
	int	type;
	char *data;
}	t_token;


typedef struct s_minishell
{
	char	*env;
	char	*line;
	t_token	*tokenizer;
}		t_minishell;


# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"

void	parser(t_minishell *minishell);

#endif