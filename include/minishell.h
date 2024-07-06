#ifndef MINISHELL_H
# define MINISHELL_H

# include "dlink_list.h"
# include "ft_printf.h"
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "stdlib.h"
# include "string.h"

typedef struct s_minishell
{
	char			*env;
	char			*line;
	int				pipe_count;
	t_dlinked_list	*tokenizer;
}					t_minishell;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"

int					parser(t_minishell *minishell);
int					quote_handler(t_minishell *minishell, int pipe_i, int sign);
void				lexer(t_minishell *minishell);


#endif
