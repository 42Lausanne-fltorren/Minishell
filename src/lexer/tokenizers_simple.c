/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizers_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:58:19 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/09 19:03:53 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	tokenize_pipe(const char *input, int *i)
{
	t_token	token;

	(void)input;
	token.type = TOKEN_PIPE;
	token.value = ft_strdup("|");
	(*i)++;
	return (token);
}

t_token	tokenize_redirect_output(const char *input, int *i)
{
	t_token	token;

	if (input[*i + 1] == '>')
	{
		token.type = TOKEN_APPEND;
		token.value = ft_strdup(">>");
		(*i)++;
	}
	else
	{
		token.type = TOKEN_OUT;
		token.value = ft_strdup(">");
	}
	(*i)++;
	return (token);
}

t_token	tokenize_redirect_input(const char *input, int *i)
{
	t_token	token;

	if (input[*i + 1] == '<')
	{
		token.type = TOKEN_HEREDOC;
		token.value = ft_strdup("<<");
		(*i)++;
	}
	else
	{
		token.type = TOKEN_IN;
		token.value = ft_strdup("<");
	}
	(*i)++;
	return (token);
}
