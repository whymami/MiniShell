/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:11:54 by btanir            #+#    #+#             */
/*   Updated: 2024/07/14 15:55:37 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signo)
{
    if (signo == SIGINT)
    {
        ft_printf("\n");
        // rl_on_new_line();
        // rl_replace_line("", 0);
        // rl_redisplay();
    }
    else if (signo == SIGQUIT)
    {
        ft_printf("\b\b  \b\b");

    }
    else if (signo == SIGTSTP)
    {
        /* code */
    }
    
    
}