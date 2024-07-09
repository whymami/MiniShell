/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/09 21:04:45 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
 #include <sys/wait.h>

void execute_command(t_minishell *minishell)
{
	// pid_t	pid;
	// int		status;
	char	**argv;
	// char	*path;
	int		i;
	t_dlist *temp;


	temp = minishell->tokens;
	i = 0;
	argv = malloc(sizeof(char *) * (dlist_size(minishell->tokens) + 1));	
	while (temp)
	{
		argv[i++] = ft_strdup((char *)temp->data);
		temp = temp->next;
	}
	argv[i] = NULL;

}
