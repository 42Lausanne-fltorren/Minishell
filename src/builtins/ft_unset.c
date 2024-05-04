/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:00:04 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/20 00:00:58 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_unsetenv(char *var, char **envp)
{
	int 	i;
	char	*split;

	i = -1;
	while (envp[++i])
	{
		split = ft_strchr(envp[i], '=');
		if (ft_strncmp(envp[i], var, split - envp[i]) == 0)
		{
			free(envp[i]);
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			break ;
		}
	}
}

int	ft_unset(t_token **args, char **envp, int fd)
{
	int i;

	(void)fd;
	if (!args || !args[0])
		return (0);
	i = -1;
	while (args[++i])
		ft_unsetenv(args[i]->value, envp);

	return (0);
}
