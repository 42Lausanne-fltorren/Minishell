/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:55:36 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/14 18:05:02 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(const char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			tokens = append_token(tokens, tokenize_single_quote(input, &i));
		else if (input[i] == '\"')
			tokens = append_token(tokens, tokenize_double_quote(input, &i));
		else if (input[i] == '|')
			tokens = append_token(tokens, tokenize_pipe(input, &i));
		else if (input[i] == '>')
			tokens = append_token(tokens, tokenize_redirect_output(input, &i));
		else if (input[i] == '<')
			tokens = append_token(tokens, tokenize_redirect_input(input, &i));
		else if (!ft_isspace(input[i]))
			tokens = append_token(tokens, tokenize_word(input, &i));
		else
			i++;
	}
	return (tokens);
}

int	is_token_type(t_token *tokens, int i, enum e_token_type type)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (tokens[j].type == TOKEN_NULL)
			return (type == TOKEN_NULL);
		j++;
	}
	return (tokens[i].type == type);
}

int	syntax_check(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_NULL)
	{
		if (tokens[i].type == TOKEN_PIPE
			&& is_token_type(tokens, i + 1, TOKEN_PIPE))
			return (0);
		if (tokens[i].type == TOKEN_HEREDOC
			&& (is_token_type(tokens, i + 1, TOKEN_IN)
				|| is_token_type(tokens, i + 1, TOKEN_HEREDOC)))
			return (0);
		if (tokens[i].type == TOKEN_APPEND
			&& (is_token_type(tokens, i + 1, TOKEN_OUT)
				|| is_token_type(tokens, i + 1, TOKEN_APPEND)))
			return (0);
		i++;
	}
	return (1);
}
