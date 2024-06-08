#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "lib/libft/libft.h"

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
		printf("Error");
	}
}

static void command_path(char **command, char *env)
{
	char **cmds;
	char *cmd;
	char *path;
	int i = -1;

	cmds = ft_split(env, ':');
	cmd = ft_strjoin("/", *command);
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

void find_path(char **cmd, char **env)
{
	while (*env)
	{
		if (strstr(*env, "PATH=") == *env)
		{
			command_path(cmd, *env);
			break;
		}
		env++;
	}
}

int main(int argc, char **argv, char **env)
{
	if (argc != 2 && printf("Error"))
		return 1;
	char **cmds;
	cmds = ft_split(argv[1], ' ');
	find_path(cmds, env);
	return 0;
}
