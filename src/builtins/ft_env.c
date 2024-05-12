/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:49:27 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:49:36 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_token **args, char ***envp, int fd)
{
	int	i;

	(void)args;
	i = 0;
	while ((*envp)[i])
	{
		ft_putstr_fd((*envp)[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	return (0);
}
