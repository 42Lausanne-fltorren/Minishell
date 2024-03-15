/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:46:35 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/14 21:02:19 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// LEXER
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_STRING,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_NULL
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token		tokenize_pipe(const char *input, int *i);
t_token		tokenize_redirect_output(const char *input, int *i);
t_token		tokenize_redirect_input(const char *input, int *i);
t_token		tokenize_word(const char *input, int *i);
t_token		tokenize_single_quote(const char *input, int *i);
t_token		tokenize_double_quote(const char *input, int *i);
int			count_tokens(t_token *tokens);
t_token		*append_token(t_token *tokens, t_token token);
t_token		*tokenize(const char *input);

// PARSER
typedef struct s_command
{
	t_token	*in;
	t_token	*heredoc;
	t_token	*cmd;
	t_token	**args;
	t_token	*out;
	t_token	*append;
}	t_command;

t_command	*parse(t_token *tokens);

t_token		**command_args_append(t_token **args, t_token *token);
t_command	*commands_append(t_command *commands, t_command tmp);

// EXPENDER
void		expand_commands(t_command *commands, char **envp);
char		*replace_variables(char *str, char **envp);
char		*ft_getenv(char *var, char **envp);
void		expand_cmd(t_token *token, char **envp);

// EXECUTOR
int			ft_commands_len(t_command *commands);
char		**ft_get_args(t_command command);
int			executor(t_command *commands, char **envp);
// MEMORY
void		free_tokens(t_token *tokens);
void		free_commands(t_command *commands);
void		ft_free_arr(char **arr);

//BUILTINS
int			ft_echo(t_command cmd);

int	ft_command_args_len(t_command command);

#endif
