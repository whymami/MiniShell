/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/27 03:36:44 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

static int ft_count_words(const char *str, char c) {
    int count = 0;
    int quote = 0;
    int in_word = 0;

    while (*str) {
        if (*str == '\'' || *str == '\"') {
            if (quote == 0) quote = *str;
            else if (quote == *str) quote = 0;
        }
        if (*str != c || quote) {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
        str++;
    }
    return count;
}

char **ft_mini_split(const char *s, char c) {
    int i = 0, j = 0, k = 0, quote = 0;
    char **dest;

    dest = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
    if (!dest) return NULL;

    while (s[i]) {
        while (s[i] && (s[i] == c && quote == 0)) i++;
        k = i;
        while (s[i] && (s[i] != c || quote)) {
            if (s[i] == '\'' || s[i] == '\"') {
                if (quote == 0) quote = s[i];
                else if (quote == s[i]) quote = 0;
            }
            i++;
        }
        if (i > k) {
            char *substr = ft_substr(s, k, i - k);
            if (substr) {
                replace_arg(&substr);
                dest[j++] = substr;
            }
        }
    }
    dest[j] = NULL;
    return dest;
}

void	*my_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
	{
		ft_printf("reallocation failed!\n");
		free(ptr);
		exit(EXIT_FAILURE);
	}
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
