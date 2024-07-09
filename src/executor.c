/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/09 21:29:50 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
 #include <sys/wait.h>

static	char **cpy_arg(t_minishell *minishell)
{
	t_dlist *temp;
	char **argv;
	int	i;

	temp = minishell->tokens;
	i = 0;
	argv = malloc(sizeof(char *) * (dlist_size(minishell->tokens) + 1));	
	while (temp)
	{
		argv[i++] = ft_strdup((char *)temp->data);
		temp = temp->next;
	}
	argv[i] = NULL;
	return (argv);
}

void execute_command(t_minishell *minishell)
{
	// pid_t	pid;
	// int		status;
	char	*path;

}
