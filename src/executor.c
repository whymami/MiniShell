#include "../include/minishell.h"
#include <unistd.h>

void	execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			ft_printf("execve hatasiii");
			exit(EXIT_FAILURE);
		}
	}
	else if(pid < 0)
	{
		ft_printf("forkhatasiiiii");
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));

	}
}

void	executor(t_minishell *minishell)
{
	int i;
	char **args;

	i = 0;
	while (minishell->tokens[i])
	{
		args = ft_split(minishell->tokens[i], ' ');
		if (args && args[0])
			execute_command(args);
		free(args[i]);
		i++;
	}
}
