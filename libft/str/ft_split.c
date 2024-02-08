/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:34 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/11 12:39:11 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**free_all(char **dest, size_t i)
{
	while (i--)
		free(dest[i]);
	free(dest);
	return (NULL);
}

static size_t	get_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	k;

	dest = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!s || !dest)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			dest[k] = ft_strndup(s + i, get_word_len(s + i, c));
			if (!dest[k])
				return (free_all(dest, k));
			k++;
			i += get_word_len(s + i, c);
		}
	}
	dest[k] = NULL;
	return (dest);
}
