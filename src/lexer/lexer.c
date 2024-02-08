/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:55:36 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 18:11:27 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*resize_tokens(t_token *tokens, int count)
{
	t_token	*new_tokens;
	int		i;

	new_tokens = (t_token *)malloc(sizeof(t_token) * (count + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_tokens[i] = tokens[i];
		i++;
	}
	new_tokens[i].type = TOKEN_EOF;
	free(tokens);
	return (new_tokens);
}

t_token	*tokenize(const char *input)
{
	t_token	*tokens;
	int		count;

	count = 0;
	tokens = (t_token *)malloc(sizeof(t_token) * (count + 1));
	if (!tokens)
		return (NULL);
	while (*input)
	{
		if (ft_isspace(*input))
			input++;
		else if (*input == '$')
		{
			tokens[count].type = TOKEN_VARIABLE;
			tokens[count].value = ft_strdup("$");
			count++;
			tokens = resize_tokens(tokens, count);
			input++;
		}
		else
		{
			tokens[count].type = TOKEN_WORD;
			tokens[count].value = ft_strdup(input);
			count++;
			tokens = resize_tokens(tokens, count);
			while (*input && !ft_isspace(*input))
				input++;
		}
	}
	tokens = resize_tokens(tokens, count);
	return (tokens);
}
