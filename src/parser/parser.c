/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:58:58 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/15 12:59:55 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	parse_command(t_token *tokens, int *i)
{
	t_command	tmp;

	tmp = (t_command){};
	while (tokens[*i].type != TOKEN_PIPE && tokens[*i].type != TOKEN_NULL)
	{
		if (tokens[*i].type == TOKEN_WORD || tokens[*i].type == TOKEN_STRING)
		{
			if (tmp.cmd == NULL)
				tmp.cmd = &tokens[*i];
			else
				tmp.args = command_args_append(tmp.args, &tokens[*i]);
		}
		else if (tokens[*i].type == TOKEN_IN)
			tmp.in = &tokens[++(*i)];
		else if (tokens[*i].type == TOKEN_OUT)
			tmp.out = &tokens[++(*i)];
		else if (tokens[*i].type == TOKEN_APPEND)
			tmp.append = &tokens[++(*i)];
		(*i)++;
	}
	return (tmp);
}

t_command	*parse(t_token *tokens)
{
	t_command	*commands;
	int			i;
	t_command	tmp;

	commands = NULL;
	i = 0;
	while (tokens[i].type != TOKEN_NULL)
	{
		tmp = parse_command(tokens, &i);
		commands = commands_append(commands, tmp);
		if (tokens[i].type != TOKEN_NULL)
			i++;
	}
	return (commands);
}
