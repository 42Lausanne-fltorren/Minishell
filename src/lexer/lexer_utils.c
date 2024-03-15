/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:41:29 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/20 16:37:12 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens[count].type != TOKEN_NULL)
		count++;
	return (count);
}

t_token	*append_token(t_token *tokens, t_token new)
{
	t_token	*tmp;
	int		count;

	if (!tokens)
		count = 0;
	else
		count = count_tokens(tokens);
	tmp = malloc(sizeof(t_token) * (count + 2));
	if (!tmp)
		return (NULL);
	count = -1;
	while (tokens && tokens[++count].type != TOKEN_NULL)
		tmp[count] = tokens[count];
	if (count == -1)
		count = 0;
	tmp[count] = new;
	tmp[count + 1].type = TOKEN_NULL;
	if (tokens)
		free(tokens);
	return (tmp);
}
