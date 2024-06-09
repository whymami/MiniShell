#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "lib/libft/libft.h"
#include <readline/readline.h>
#include <string.h>
#include <sys/wait.h>

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

static void command_path(char *command, char *env)
{
	if (ft_strncmp(command, "clear", ft_strlen(command)) == 0 && printf("\033[H\033[J"))
        return;

    char **paths = ft_split(env, ':');
    char **cmds = ft_split(command, ' ');
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

int main()
{
    char *line;
    char *env = getenv("PATH");

    while (1)
    {
        line = readline(STYLE_BOLD COLOR_YELLOW "minishell> " COLOR_RESET);
        if (*line)
		{
			add_history(line);
            command_path(line, env);
		}
        free(line);
    }

    return 0;
}
