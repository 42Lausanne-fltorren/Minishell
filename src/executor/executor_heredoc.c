/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:07:38 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 14:46:01 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_command cmd, int *pipe)
{
	char	*delimiter;
	int		i;

	delimiter = cmd.heredoc[0]->value;
	i = 1;
	while (cmd.heredoc[i])
	{
		if (ft_strncmp(cmd.heredoc[i]->value, delimiter,
				ft_strlen(cmd.heredoc[i]->value)) == 0)
			break ;
		if (i > 1 && ft_strchr(cmd.heredoc[i - 1]->value, '\n') == NULL)
			ft_putstr_fd(" ", pipe[1]);
		ft_putstr_fd(cmd.heredoc[i]->value, pipe[1]);
		i++;
	}
}
