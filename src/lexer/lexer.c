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
