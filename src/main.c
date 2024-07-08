/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/08 16:23:36 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (EXIT_FAILURE); //hata mesajı
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (ft_strlen(minishell->line) != 0)
			add_history(minishell->line);
		// if(!parser(minishell))
		// 	lexer(minishell); // lexer parserin içine taşıncak ve bu kısıma executor gelcek.
	}
	return (SUCCESS);
}
