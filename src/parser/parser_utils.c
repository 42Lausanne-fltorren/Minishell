/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:47:42 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/14 17:53:37 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**command_args_append(t_token **args, t_token *token)
{
	int		i;
	t_token	**new_args;

	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc(sizeof(t_token *) * (i + 2));
	if (new_args == NULL)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = token;
	new_args[i + 1] = NULL;
	if (args)
		free(args);
	return (new_args);
}

t_command	*commands_append(t_command *commands, t_command tmp)
{
	int			i;
	t_command	*new_commands;

	i = 0;
	while (commands && commands[i].cmd)
		i++;
	new_commands = malloc(sizeof(t_command) * (i + 2));
	if (new_commands == NULL)
		return (NULL);
	i = 0;
	while (commands && commands[i].cmd)
	{
		new_commands[i] = commands[i];
		i++;
	}
	new_commands[i] = tmp;
	new_commands[i + 1] = (t_command){};
	if (commands)
		free(commands);
	return (new_commands);
}

int	command_args_len(t_token **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

char	*open_error(char *file)
{
	char	*error;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", file);
	error = ft_strjoin(tmp, ": ");
	free(tmp);
	tmp = ft_strjoin(error, strerror(errno));
	free(error);
	error = ft_strjoin(tmp, "\n");
	free(tmp);
	return (error);
}
