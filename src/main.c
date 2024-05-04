/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:07 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:22:35 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int	last_command_exit_status = 0;
	const char *input = "echo hello'\"\"world'";
	t_token *tokens = tokenize(input);
	t_command *commands = parse(tokens);
	int i = 0;
	ft_printf("========== LEXER ==========\n");
	ft_printf("input(len: %d): %s\n", ft_strlen(input), input);
	while (tokens[i].type != TOKEN_NULL)
	{
		ft_printf("Token[%d]: (%d, %s)\n", i, tokens[i].type, tokens[i].value);
		i++;
	}
	ft_printf("========== PARSER ==========\n");
	i = 0;
	while (commands[i].cmd)
	{
		ft_printf("Command[%d]: %s\n\tArgs: ", i, commands[i].cmd->value);
		if (commands[i].args)
		{
			int j = 0;
			while (commands[i].args[j])
			{
				ft_printf("'%s' ", commands[i].args[j]->value);
				j++;
			}
		} else
			ft_printf("NULL");
		ft_printf("\tHerdoc: ");
		if (commands[i].heredoc)
		{
			int j = 0;
			while (commands[i].heredoc[j])
			{
				ft_printf("%s ", commands[i].heredoc[j]->value);
				j++;
			}
		} else
			ft_printf("NULL");
		if (commands[i].in)
			ft_printf("\n\tInput: %s", commands[i].in->value);
		if (commands[i].out)
			ft_printf("\n\tOutput: %s", commands[i].out->value);
		if (commands[i].append)
			ft_printf("\n\tAppend: %s", commands[i].append->value);
		ft_printf("\n");
		i++;
	}
	expand_commands(commands, envp, last_command_exit_status);
	ft_printf("========== EXPANDER ==========\n");
	i = 0;
	while (commands[i].cmd)
	{
		ft_printf("Command[%d]: %s (Builtin: %d)\n\tArgs: ", i, commands[i].cmd->value, commands[i].builtin);
		if (commands[i].args)
		{
			int j = 0;
			while (commands[i].args[j])
			{
				ft_printf("%s ", commands[i].args[j]->value);
				j++;
			}
		} else
			ft_printf("NULL");
		if (commands[i].in)
			ft_printf("\n\tInput: %s", commands[i].in->value);
		if (commands[i].out)
			ft_printf("\n\tOutput: %s", commands[i].out->value);
		if (commands[i].append)
			ft_printf("\n\tAppend: %s", commands[i].append->value);
		ft_printf("\n");
		i++;
	}
	last_command_exit_status = executor(commands, envp);
	ft_printf("Last command exit status: %d\n", last_command_exit_status);
	free_tokens(tokens);
	free_commands(commands);
	return (0);
}*/

int	event(void)
{
	return (0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

void	ft_init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	rl_event_hook = event;
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
}

int	handle_input(char *input, char **envp, int last_command_exit_status)
{
	t_token		*tokens;
	t_command	*commands;

	add_history(input);
	tokens = tokenize(input);
	commands = parse(tokens);
	expand_commands(commands, envp, last_command_exit_status);
	last_command_exit_status = executor(commands, envp);
	free_tokens(tokens);
	free_commands(commands);
	return (last_command_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	int			exit_status;

	ft_init(argc, argv);
	while (1)
	{
		input = get_input();
		if (!input)
			break ;
		if (ft_strlen(input) > 0)
			exit_status = handle_input(input, envp, exit_status);
		free(input);
		if (!isatty(STDIN_FILENO))
			exit(exit_status);
	}
	exit(exit_status);
}

/*int	main(void)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execve("/bin/wc", (char *[]){"wc", "-c", NULL}, NULL);
		perror("execve");
		exit(1);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_pwd(0, 0);
		close(pipefd[1]);
		close(STDOUT_FILENO);
		waitpid(pid, NULL, 0);
	}
}*/

/*int	main(int argc, char **argv, char **envp)
{
	t_command	*commands;
	t_token		token_1;
	t_token		token_2;

	(void)argc;
	(void)argv;
	commands = malloc(sizeof(t_command) * 2);
	commands[0].cmd = &token_1;
	commands[0].cmd->value = malloc(sizeof(char *));
	commands[0].cmd->value = "pwd";
	commands[0].args = NULL;
	commands[0].builtin = ft_pwd;

	commands[1].cmd = &token_2;
	commands[1].cmd->value = malloc(sizeof(char *));
	commands[1].cmd->value = "/bin/wc";
	commands[1].args = NULL;


	// expand_commands(commands, envp, 0);
	executor(commands, envp);
	free_commands(commands);
	return (0);
}*/
