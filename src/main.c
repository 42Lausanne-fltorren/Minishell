/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:07 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 17:59:43 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	const char *input = "echo $HOME > file.txt";
	const t_token *tokens = tokenize(input);
	int i = 0;
	while (tokens[i].type != TOKEN_EOF)
	{
		ft_printf("Token: %s\n", tokens[i].value);
		i++;
	}

	return (0);
}
