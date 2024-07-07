/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:37:13 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 14:41:12 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*parse_equals(char *env)
{
	int y;
	t_env *env_data;
	int	flag = 0;

	y = -1;
	env_data = malloc(sizeof(env_data));
	while (env[++y])
	{
		if (flag == 0 && env[y] == '=')
		{
			env_data->key = ft_substr(env, 0, y);
			flag = 1;
		}
		else if (flag == 1)
		{
			env_data->value = ft_substr(env, y, ft_strlen(env) - y);
			break;
		}
	}
	return (env_data);
}

void parse_env(t_minishell *minishell, char **env)
{
	int i;

	i = 0;
	minishell->env = ft_lstnew(parse_equals(env[0]));
	// if(!minishell->env)
	// 	return(EXIT_FAILURE); //error check yapılacak

	//while ile her satırı tek tek yolla
	while (env[++i])
		ft_lstadd_back(&minishell->env,ft_lstnew(parse_equals(env[i])));

	while (minishell->env)
	{
		t_env *a = (t_env *)minishell->env->content;

		printf("%s\t=\t",a->key);
		printf("%s\n",a->value);

		minishell->env = minishell->env->next;
	}

}
