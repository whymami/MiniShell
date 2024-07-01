/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:48:50 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/01 15:10:52 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_split(char **split)
{
    int i = -1;
    while (split[++i])
        free(split[i]);
    free(split);
}

void execute_cmd(char *path, char **command)
{
    if (execve(path, command, NULL) == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}

void create_fork(char *path, char **command)
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
        execute_cmd(path, command);
    else if (pid < 0)
        perror("Error");
    else
        waitpid(pid, &status, 0);
}

void command_path(t_minishell *mini)
{
	if (ft_strncmp(mini->line, "clear", ft_strlen(mini->line)) == 0 && printf("\033[H\033[J"))
        return;

    char **paths = ft_split(mini->env, ':');
    char **cmds = ft_split(mini->line, ' ');
    char *cmd_with_slash = ft_strjoin("/", cmds[0]);
	char *path;

    int i = -1;
    while (paths[++i])
    {
		path = ft_strjoin(paths[i], cmd_with_slash);
        if (access(path, F_OK) == 0)
        {
            cmds[0] = ft_strtrim(cmds[0], "/");
            create_fork(path, cmds);
            return;
        }
        free(path);
    }
	printf(COLOR_YELLOW STYLE_BOLD"minishell>" COLOR_RESET " %s: command not found\n", cmds[0]);
}

void pipe_count(t_minishell *mini)
{
	int i = -1;
	while (mini->line[++i])
		if (mini->line[i] == '|')
			mini->pipe->pipe_count++;
}

int main()
{
	t_minishell *mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	mini->pipe = ft_calloc(1, sizeof(t_pipe));
	
	mini->env = getenv("PATH");
    while (1)
    {
        mini->line = readline(STYLE_BOLD COLOR_YELLOW "minishell> " COLOR_RESET);
		if (str)
        if (*mini->line && ft_strlen(mini->line) > 0) 
		{
			add_history(mini->line);
            command_path(mini);
		}
        free(mini->line);
    }
    return (0);
}
