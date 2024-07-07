/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 12:56:40 by btanir           ###   ########.fr       */
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
		if(!parser(minishell))
			lexer(minishell); // lexer parserin içine taşıncak ve bu kısıma executor gelcek.
	}
	return (EXIT_SUCCESS);
}
