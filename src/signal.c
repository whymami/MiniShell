/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:11:54 by btanir            #+#    #+#             */
/*   Updated: 2024/08/02 21:14:18 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ctrl_d(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\033[K");
	rl_redisplay();
	g_sig = 0;
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (g_sig == IN_HEREDOC)
	{
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
	else if (g_sig == IN_CMD)
	{
		rl_on_new_line();
		g_sig = AFTER_CMD;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sig = 1;
}

void	tcseta(void)
{
	struct termios	term1;

	if (tcgetattr(STDIN_FILENO, &term1) != 0)
		exit((perror("error"), -1));
	else
	{
		term1.c_cc[VQUIT] = _POSIX_VDISABLE;
		term1.c_lflag |= ECHOE | ICANON;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
			exit((perror("error"), -1));
		if (tcgetattr(STDIN_FILENO, &term1) != 0)
			exit((perror("error"), -1));
	}
}

void	handle_signals(void)
{
	tcseta();
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_d);
}
