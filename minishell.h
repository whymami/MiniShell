/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:47:42 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/01 15:10:17 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>

# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_RESET   "\x1b[0m"
# define STYLE_BOLD    "\x1b[1m"

typedef struct s_pipe
{
	int pipe_count;
	int *pipe_fd;
}	t_pipe;

typedef struct s_minishell
{
	t_pipe *pipe;
	char *line;
	char *env;
}	t_minishell;

void pipe_command(t_minishell *mini);
void create_fork(char *path, char **command);
void free_split(char **split);
void execute_cmd(char *path, char **command);
void command_path(t_minishell *mini);

#endif