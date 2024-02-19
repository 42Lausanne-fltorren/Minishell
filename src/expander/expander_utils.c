/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:31:40 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/15 13:01:34 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var + 1);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var + 1, len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/*
	Takes a string and replaces the first occurence of var with value.
*/
static char	*ft_replace_str(char *str, char *var, char *value)
{
	char	*new;
	char	*ptr;
	int		len;

	ptr = ft_strnstr(str, var, ft_strlen(str));
	if (!ptr)
		return (str);
	len = ptr - str;
	new = ft_calloc(len + ft_strlen(value) + ft_strlen(ptr + ft_strlen(var))
			+ 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, str, len + 1);
	ft_strlcat(new, value, len + ft_strlen(value) + 1);
	ft_strlcat(new, ptr + ft_strlen(var), len + ft_strlen(value) + ft_strlen(ptr
			+ ft_strlen(var)) + 1);
	free(str);
	return (new);
}

char	*replace_variables(char *str, char **envp)
{
	int		i;
	int		j;
	char	*var;
	char	*value;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			j = 1;
			while (str[i + j] && !ft_isspace(str[i + j]) && str[i + j] != '$')
				j++;
			var = ft_substr(str, i, j);
			value = ft_getenv(var, envp);
			str = ft_replace_str(str, var, value);
			free(var);
		}
		i++;
	}
	return (str);
}
