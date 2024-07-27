/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_direct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:55:19 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/27 20:20:25 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
static char *handle_quotes(const char *str)
{
    char *result;
    int i, j;

    if (!str)
        return NULL;

    result = malloc(strlen(str) + 1);
    if (!result)
        return NULL;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != '"' && str[i] != '\'')
        {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';

    return result;
}

static int rdirect_out(char *file, int append)
{
    int fd;
    char *clean_file;

    clean_file = handle_quotes(file);
    if (append)
    {
        fd = open(clean_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    }
    else
    {
        fd = open(clean_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    }
    free(clean_file);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: No such file or directory\n", 2);
        return 1;
    }
    if (fd >= 0)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("minishell: ");
            close(fd);
            return 1;
        }
    }
    return (close(fd), 0);
}

static int rdirect_in(char *file)
{
    int fd;
    char *clean_file;

    clean_file = handle_quotes(file);
    fd = open(clean_file, O_RDONLY);
    free(clean_file);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: No such file or directory\n", 2);
        return 1;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: ");
        close(fd);
        return 1;
    }
    return (close(fd), 0);
}

static int ft_rdirect(t_minishell *mini, char **args)
{
    int j;
    char *file;
    int i;

    j = 0;
    i = 0;
    if (mini->g_fd.change == 0)
    {
        mini->g_fd.std_in = dup(0);
        mini->g_fd.std_out = dup(1);
        mini->g_fd.change = 1;
    }
    while (args[j])
    {
        if ((ft_strcmp(args[j], ">") == 0 && args[j + 1]) || (ft_strcmp(args[j], ">>") == 0 && args[j + 1]))
        {
            file = args[j + 1];
            if (ft_strcmp(args[j], ">") == 0)
            {
                if (rdirect_out(file, 0))
                    return 1;
            }
            else if (rdirect_out(file, 1))
                return 1;
            free(args[j]);
            free(args[j + 1]);
            args[j] = NULL;
            args[j + 1] = NULL;
            j += 2;
        }
        else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
        {
            file = args[j + 1];
            if (rdirect_in(file))
                return 1;
            free(args[j]);
            free(args[j + 1]);
            args[j] = NULL;
            args[j + 1] = NULL;
            j += 2;
        }
        else
            args[i++] = args[j++];
    }
    args[i] = NULL;
    return 0;
}

void	replace_arg(char **args)
{
	char	*input;
	int		len;
	char	*buffer;
	int		i;
	int		j;

	input = *args;
	len = strlen(input);
	buffer = (char *)malloc((len * 2) + 1);
	if (!buffer)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (i < len)
	{
		if ((input[i] == '>' || input[i] == '<') && check_quote(input, i) == 0)
		{
			if (i > 0 && input[i - 1] != ' ')
				buffer[j++] = ' ';
			if (input[i] == '>' && input[i + 1] == '>')
			{
				buffer[j++] = '>';
				buffer[j++] = '>';
				i += 2;
			}
			else if (input[i] == '<' && input[i + 1] == '<')
			{
				buffer[j++] = '<';
				buffer[j++] = '<';
				i += 2;
			}
			else
			{
				buffer[j++] = input[i++];
			}
			if (i < len && input[i] != ' ')
				buffer[j++] = ' ';
		}
		else
		{
			buffer[j++] = input[i++];
		}
	}
	buffer[j] = '\0';
	free(*args);
	*args = buffer;
}

int	check_direct(t_minishell *mini, char **args)
{
	int	j;

	j = -1;
	while ((args)[++j])
	{
		if (ft_strcmp((args)[j], ">") == 0 || ft_strcmp((args)[j], "<") == 0
			|| ft_strcmp((args)[j], ">>") == 0)
		{
			if (ft_rdirect(mini, args))
				return (mini->exit_code = 1, 1);
			return (0);
		}
	}
	return (SUCCESS);
}
