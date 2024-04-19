/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:57:58 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 14:29:14 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_get_heredoc_marker(char *input)
{
	char	*start_pos;
	char	*end_pos;

	if (!input)
		return (NULL);
	start_pos = ft_strnstr(input, "<<", ft_strlen(input));
	if (!start_pos)
		return (NULL);
	end_pos = ft_strchr(start_pos + 2, '\n');
	if (!end_pos)
		end_pos = ft_strchr(start_pos + 2, '\0');
	if (!end_pos || (end_pos - start_pos) < 2)
		return (NULL);
	return (ft_substr(start_pos + 2, 0, end_pos - start_pos - 2));
}

int	is_heredoc_done(char *input)
{
	char	*start_pos;
	char	*end_pos;
	char	*marker;
	char	*tmp;

	marker = ft_get_heredoc_marker(input);
	tmp = ft_strtrim(marker, " \t");
	free(marker);
	marker = tmp;
	if (!marker)
		return (1);
	start_pos = ft_strnstr(input, marker, ft_strlen(input));
	if (!start_pos)
	{
		free(marker);
		return (0);
	}
	end_pos = ft_strnstr(start_pos + ft_strlen(marker), marker, ft_strlen(input)
			- (start_pos - input + ft_strlen(marker)));
	free(marker);
	return (end_pos != NULL);
}
