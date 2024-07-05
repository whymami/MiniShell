/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/05 04:14:31 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

int	main(void)
{
	t_minishell *minishell;

	minishell = malloc(sizeof(t_minishell));
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (strlen(minishell->line) != 0)
			add_history(minishell->line);
		parser(minishell);
	}
	return (EXIT_SUCCESS);
}
