/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:46:35 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:59:32 by fltorren         ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>

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

typedef int	(*t_builtin)(t_token **args, char **envp, int fd);
// PARSER
typedef struct s_command
{
	t_token		*in;
	t_token		**heredoc;
	t_token		*cmd;
	t_token		**args;
	t_token		*out;
	t_token		*append;
	t_builtin	builtin;
}	t_command;

t_command	*parse(t_token *tokens);

int			command_args_len(t_token **args);
t_token		**command_args_append(t_token **args, t_token *token);
t_command	*commands_append(t_command *commands, t_command tmp);

// EXPENDER
void		expand_commands(t_command *commands, char **envp, int lces);
char		*replace_variables(char *str, char **envp);
void		clear_closed_brackets(char *str);
char		*ft_replace_str(char *str, char *var, char *value);
char		*ft_getenv(char *var, char **envp);
void		expand_cmd(t_token *token, char **envp);

// EXECUTOR
int			ft_commands_len(t_command *commands);
char		**ft_get_args(t_command command);
int			executor(t_command *commands, char **envp);
void		ft_io_error(char *file);
void		ft_setup_io(int **pipes, int i, int cmd_count, t_command cmd);
void		ft_close(int **pipes, int cmd_count);
void		ft_wait(int cmd_count, pid_t *pids, int *status);
void		ft_heredoc(t_command cmd, int *pipe);
void		ft_free_all(int **pipes, pid_t *pids, int cmd_count);
int			**ft_init_pipes(int cmd_count, pid_t *pids);

// MEMORY
void		free_tokens(t_token *tokens);
void		free_commands(t_command *commands);
void		ft_free_arr(char **arr);

//BUILTINS
int			ft_echo(t_token **args, char **envp, int fd);
int			ft_pwd(t_token **args, char **envp, int fd);
int			ft_cd(t_token **args, char **envp, int fd);
int			ft_env(t_token **args, char **envp, int fd);
int			ft_exit(t_token **args, char **envp, int fd);
int			ft_export(t_token **args, char **envp, int fd);
int			ft_unset(t_token **args, char **envp, int fd);

//INPUT
char		*get_input(void);
char		*ft_get_heredoc_marker(char *input);
int			is_heredoc_done(char *input);
#endif
