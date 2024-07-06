/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/06 16:37:57 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

int	main(void)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (ft_strlen(minishell->line) != 0)
			add_history(minishell->line);
		parser(minishell);
		lexer(minishell);
		executor(minishell);
	}
	return (EXIT_SUCCESS);
}
