/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:46:21 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/04 12:33:32 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

int		g_sig = 0;

void	init_data(t_minishell *minishell, int i)
{
	if (i == 1)
	{
		minishell->line = NULL;
		minishell->hrd_cmd = NULL;
		minishell->pipe_fd = NULL;
		minishell->pid = NULL;
		minishell->oldpwd = NULL;
		minishell->tokens = NULL;
		minishell->env = NULL;
		minishell->args = NULL;
	}
	minishell->pipe_count = 0;
	minishell->hrd_count = 0;
	minishell->sign = 0;
	minishell->in_heredoc = 0;
	minishell->fd_handler.change = 0;
}

int	minishell_routine(t_minishell *minishell)
{
	add_history(minishell->line);
	if (!parser(minishell))
	{
		dollar(minishell, 0);
		lexer(minishell);
		if (cpy_arg(minishell))
			return (FAILURE);
		if (heredoc(minishell))
		{
			if (minishell->args)
				free_args(minishell->args);
			if (minishell->args_with_quotes)
				free_args(minishell->args_with_quotes);
			if (minishell->tokens)
				dlist_clear(&minishell->tokens, del);
			if (minishell->line)
				free(minishell->line);
			if (minishell->heredoc_fd)
				free(minishell->heredoc_fd);
			return (2);
		}
		execute_command(minishell);
	}
	return (SUCCESS);
}

int	shell_loop(t_minishell *minishell)
{
	int	value;

	while (1)
	{
		value = 0;
		init_data(minishell, 0);
		minishell->line = readline("minishell> ");
		if (minishell->line == NULL)
		{
			ft_putstr_fd("exit\n", 0);
			rl_clear_history();
			exit(0);
		}
		if (ft_strlen(minishell->line) != 0)
		{
			value = minishell_routine(minishell);
			if (value == 2)
				continue ;
			else if (value == 1)
				return (FAILURE);
		}
		if (minishell->line)
			free(minishell->line);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	handle_signals();
	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2),
			EXIT_FAILURE);
	init_data(minishell, 1);
	parse_env(minishell, env);
	shell_loop(minishell);
	return (SUCCESS);
}
