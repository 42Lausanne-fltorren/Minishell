/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:58:58 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 13:44:53 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_string(t_command *tmp, t_token *tokens, int *i, int heredoc)
{
	if (tmp->cmd == NULL)
	{
		if (tokens[*i].value[0] != '\0')
			tmp->cmd = &tokens[*i];
	}
	else if (heredoc)
		tmp->heredoc = command_args_append(tmp->heredoc, &tokens[*i]);
	else
		tmp->args = command_args_append(tmp->args, &tokens[*i]);
}

void	parse_in(t_command *tmp, t_token *tokens, int *i)
{
	int		fd;
	t_token	t;

	t = tokens[++(*i)];
	clear_closed_brackets(t.value);
	fd = open(t.value, O_RDONLY, 0644);
	if (fd == -1 && !tmp->open_error)
		tmp->open_error = open_error(t.value);
	else
	{
		tmp->in = &tokens[*i];
		close(fd);
	}
}

void	parse_out(t_command *tmp, t_token *tokens, int *i)
{
	int		fd;
	int		oflag;
	t_token	t;

	if (tmp->open_error)
		return ;
	if (tokens[*i].type == TOKEN_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	t = tokens[++(*i)];
	clear_closed_brackets(t.value);
	fd = open(t.value, oflag, 0644);
	if (fd == -1 && !tmp->open_error)
		tmp->open_error = open_error(t.value);
	else
	{
		if (tokens[(*i) - 1].type == TOKEN_OUT)
			tmp->out = &tokens[*i];
		else
			tmp->append = &tokens[*i];
		close(fd);
	}
}

t_command	parse_command(t_token *tokens, int *i)
{
	t_command	tmp;
	int			heredoc;

	tmp = (t_command){};
	heredoc = 0;
	while (tokens[*i].type != TOKEN_PIPE && tokens[*i].type != TOKEN_NULL)
	{
		if (tokens[*i].type == TOKEN_WORD || tokens[*i].type == TOKEN_STRING)
			parse_string(&tmp, tokens, i, heredoc);
		else if (tokens[*i].type == TOKEN_IN)
			parse_in(&tmp, tokens, i);
		else if (tokens[*i].type == TOKEN_OUT
			|| tokens[*i].type == TOKEN_APPEND)
			parse_out(&tmp, tokens, i);
		else if (tokens[*i].type == TOKEN_HEREDOC)
			heredoc = 1;
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
