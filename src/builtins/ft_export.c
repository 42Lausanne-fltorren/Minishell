/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:59:39 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/20 00:00:54 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_to_env(char *key_value, char ***envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[i] = ft_strdup(key_value);
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}

static int	is_valid(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

int	ft_export(t_token **args, char ***envp, int fd)
{
	int	i;

	(void)fd;
	if (!args || !args[0])
		return (0);
	i = -1;
	while (args[++i])
	{
		if (!is_valid(args[i]->value))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(args[i]->value, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
	}
	i = -1;
	while (args[++i])
		add_to_env(args[i]->value, envp);
	return (0);
}
