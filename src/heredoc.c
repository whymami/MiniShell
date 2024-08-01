/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:02 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/29 21:13:51 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
int check_heredoc_syntax_errors(char **args)
{
    int i;
    int len;

    i = 0;
    while (args[i])
    {
        len = strlen(args[i]);
        if (len >= 2 && strncmp(args[i], "<<", 2) == 0)
        {
            if (len > 2)
            {
                err_msg(SYNTAX_ERR, "`<<'", NULL);
                return (1);
            }
            if (args[i + 1] && strncmp(args[i + 1], ">>", 2) == 0)
            {
                err_msg(SYNTAX_ERR, "`>>'", NULL);
                return (1);
            }
            if (args[i + 1] && strncmp(args[i + 1], "<<", 2) == 0)
            {
                err_msg(SYNTAX_ERR, "`<<'", NULL);
                return (1);
            }
        }
        i++;
    }
    return (0);
}

static int	process_delimiters(t_minishell *mini, char ***delimiters)
{
	char	***args;
	char	**temp_delimiters;
	int		i;

	args = mini->args;
	i = -1;
	while (++i <= mini->pipe_count)
	{
		temp_delimiters = get_delimiters(mini, args[i]);
		if (temp_delimiters)
		{
			*delimiters = merge_delimiters(*delimiters, temp_delimiters);
			if (!*delimiters)
				return (0);
		}
	}
	return (1);
}

static int	read_heredoc(char **delimiters)
{
	char	*line;
	int		j;

	j = 0;
	while (delimiters[j])
	{
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, delimiters[j]) == 0)
			{
				free(delimiters[j]);
				j++;
				free(line);
				break ;
			}
			free(line);
		}
		if (!line)
			break ;
	}
	while (delimiters[j])
		free(delimiters[j++]);
	free(delimiters);
	return (0);
}

int	heredoc(t_minishell *mini)
{
	char	**delimiters;
	char	***args;
	int		i;

	delimiters = NULL;
	args = mini->args;
	i = -1;
	if (!args)
		return (0);
	while (args[++i])
    {
        if (check_heredoc_syntax_errors(args[i])) {
            mini->exit_code = 2;
            return (FAILURE);
        }
    }
	i = 0;
	if (!process_delimiters(mini, &delimiters) || !delimiters || !delimiters[0])
		return (ft_printf("%s%s `newline'\n", ERR_TITLE, SYNTAX_ERR),
			mini->exit_code = 2, 1);
	read_heredoc(delimiters);
	while (i <= mini->pipe_count)
		null_heredoc_args(args[i++]);
	return (SUCCESS);
}
