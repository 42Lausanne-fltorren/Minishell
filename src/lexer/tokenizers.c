/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:06:55 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/09 19:16:51 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	tokenize_word(const char *input, int *i)
{
	t_token	token;
	int		j;

	token.type = TOKEN_WORD;
	j = *i;
	while (input[j] && !ft_strchr(" \t|><", input[j]))
		j++;
	token.value = ft_substr(input, *i, j - (*i));
	(*i) = j;
	return (token);
}

t_token	tokenize_single_quote(const char *input, int *i)
{
	t_token	token;
	int		j;

	token.type = TOKEN_STRING;
	j = *i + 1;
	while (input[j] && input[j] != '\'')
		j++;
	token.value = ft_substr(input, *i + 1, j - *i - 1);
	(*i) = j + 1;
	return (token);
}

t_token	tokenize_double_quote(const char *input, int *i)
{
	t_token	token;
	int		j;

	token.type = TOKEN_STRING;
	j = *i + 1;
	while (input[j] && input[j] != '\"')
		j++;
	token.value = ft_substr(input, *i + 1, j - *i - 1);
	(*i) = j + 1;
	return (token);
}
