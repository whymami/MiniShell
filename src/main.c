/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:46:21 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/01 18:30:32 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

void	init_data(t_minishell *minishell)
{
	minishell->line = NULL;
	minishell->pipe_count = 0;
	minishell->hrd_cmd = NULL;
	minishell->pipe_fd = NULL;
	minishell->pid = NULL;
	minishell->oldpwd = NULL;
	minishell->tokens = NULL;
	minishell->env = NULL;
	minishell->args = NULL;
	minishell->exit_code = 0;
	minishell->sign = 0;
	minishell->in_heredoc = 0;
	minishell->g_fd.change = 0;
}

int	shell_loop(t_minishell *minishell)
{
	while (1)
	{
		minishell->hrd_count = 0;
		minishell->sign = 0;
		minishell->pipe_count = 0;
		minishell->in_heredoc = 0;
		minishell->g_fd.change = 0;
		minishell->line = readline("minishell> ");
		if (minishell->line == NULL)
		{
			ft_putstr_fd("exit\n", 0);
			rl_clear_history();
			exit(0);
		}
		if (ft_strlen(minishell->line) != 0)
		{
			add_history(minishell->line);
			if (!parser(minishell))
			{
				dollar(minishell, 0);
				lexer(minishell);
				if (cpy_arg(minishell))
					return (FAILURE);
				if (minishell->hrd_count > 0)
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
						continue ;
					}
				if (minishell->in_heredoc == 1)
				{
					minishell->in_heredoc = 0;
					continue ;
				}
				execute_command(minishell);
			}
		}
		if (minishell->line)
			free(minishell->line);
	}
	return (SUCCESS);
}
#include "termios.h"
void	tcsa(void)
{
	struct termios	term1;

	if (tcgetattr(STDIN_FILENO, &term1) != 0)
		exit((perror("error"), -1));
	else
	{
		term1.c_cc[VQUIT] = _POSIX_VDISABLE;
		term1.c_lflag |= ECHOE | ICANON;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
			exit((perror("error"), -1));
		if (tcgetattr(STDIN_FILENO, &term1) != 0)
			exit((perror("error"), -1));
	}
}


int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	g_status = 0;
	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2),
			EXIT_FAILURE);
	init_data(minishell);
	tcsa();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	parse_env(minishell, env);
	shell_loop(minishell);
	return (SUCCESS);
}
