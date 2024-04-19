/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:14:59 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 14:26:21 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_input_text(void)
{
	char	*pwd;
	char	*input_text;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("minishell: pwd: %s\n", strerror(errno));
		return (NULL);
	}
	tmp = ft_strjoin("\e[1;32mMinishell:\e[1;34m", pwd);
	input_text = ft_strjoin(tmp, "\e[0m$ ");
	free(pwd);
	free(tmp);
	return (input_text);

}

int	ft_get_heredoc_pos(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '<')
		i++;
	if (input[i] == '<')
	{
		i++;
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
	}
	return (i);
}

char	*get_input(void)
{
	char	*input_text;
	char	*input;
	char	*tmp;
	char	*tmp2;

	input_text = get_input_text();
	input = readline(input_text);
	while (!is_heredoc_done(input))
	{
		tmp = ft_strjoin(input, "\n");
		free(input);
		tmp2 = readline("> ");
		input = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
	}
	free(input_text);
	return (input);
}
