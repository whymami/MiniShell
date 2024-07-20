/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:11:54 by btanir            #+#    #+#             */
/*   Updated: 2024/07/20 13:03:27 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signo)
{
    if (signo == SIGINT)
    {
        ft_printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
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