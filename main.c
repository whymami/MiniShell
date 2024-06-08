#include "stdio.h"
#include "unistd.h"
#include "lib/libft/libft.h"
#include "readline/readline.h"
#include "string.h"

#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"
#define STYLE_BOLD    "\x1b[1m"

void free_split(char **split)
{
	int i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
void execute_cmd(char *path, char *command)
{
	char *args[] = {command, NULL};
	if (execve(path, args, NULL) == -1)
	{
		perror("Error");
	}
}


static void command_path(char *command, char *env)
{
	char **cmds;
	char *cmd;
	char *path;
	int i = -1;

	cmds = ft_split(env, ':');
	cmd = ft_strjoin("/", command);
	while (cmds[++i])
	{
		path = ft_strjoin(cmds[i], cmd);
		if (access(path, F_OK) == 0)
		{
			free_split(cmds);
			free(cmd);
			break;
		}
		free(path);
	}
	execute_cmd(path , command);
}

int main()
{
	char *line;
	char *env;

	env = getenv("PATH");
	while (1)
	{
		line = readline(STYLE_BOLD COLOR_YELLOW"minishell> "COLOR_RESET);
		if (!line)
			break;
		command_path(line, env);
		free(line);
	}
	return 0;
}

