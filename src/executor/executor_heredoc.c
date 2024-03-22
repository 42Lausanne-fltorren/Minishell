/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:07:38 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/18 15:47:47 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_command cmd, int *pipe)
{
	char	*delimiter;
	char	*value;
	int		i;
	char	*sub;

	delimiter = ft_strdup("");
	value = ft_strdup("");
	i = 0;
	while (cmd.heredoc[i] && ft_strchr(delimiter, '\n') == NULL)
	{
		delimiter = ft_strjoin(delimiter, cmd.heredoc[i]->value);
		i++;
	}
	delimiter = ft_substr(delimiter, 0, ft_strlen(delimiter) - 1);
	while (cmd.heredoc[i])
	{
		value = ft_strjoin(value, cmd.heredoc[i]->value);
		i++;
		if (cmd.heredoc[i])
			value = ft_strjoin(value, " ");
	}
	i = (int)(ft_strnstr(value, delimiter, ft_strlen(value)) - value);
	sub = ft_substr(value, 0, i);
	ft_putstr_fd(sub, pipe[1]);
	free(delimiter);
	free(value);
	free(sub);
}
