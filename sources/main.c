/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/11 17:03:43 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/token.h"
#include "../include/executer.h"
#include "../include/builtins.h"
#include "../include/signals.h"

int	shell_signal;

int	number_of_tasks(t_token *tokens)
{
	int	i;
	int	number;

	i = -1;
	number = 1;
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE)
			number++;
	}
	return (number);
}

int	process_line(t_session *session, char *line)
{
	session->tokens = tokenize(line);
	if (!session->tokens)
		return (0);
	session->ntasks = number_of_tasks(session->tokens);
	session->operators = operator_rules(session->tokens);
	if (!session->operators)
		return (free_session(session));
	session->pipes = create_pipes(session->operators);
	if (!session->pipes)
		return (free_session(session));
	session->readfrom = obtain_read_documents(session->tokens,
			session->pipes, session->ntasks);
	if (!session->readfrom)
		return (free_session(session));
	session->commands = obtain_commands(session->tokens, session->ntasks);
	if (!session->commands)
		return (free_session(session));
	session->writeto = obtain_write_documents(session->tokens, session->ntasks);
	if (!session->writeto)
		return (free_session(session));
	print_session(session);
	perform_tasks(session);
	printf("tasks were performed :)\n");
	return (free_session(session));
}

void	read_evaluate_print_loop(t_session *session)
{
	session->line = readline("<Minishell> ");
	while (session->line || shell_signal == SIGINT)
	{
		shell_signal = 0;
		if (!ft_strncmp(session->line, "exit", 4) && ft_strlen(session->line) == 4)
		{
			free(session->line);
			rl_clear_history();
			break ;
		}
		if (ft_strlen(session->line) > 0)
		{
			add_history(session->line);
			process_line(session, session->line);

		}
		session->line = readline("<Minishell> ");
	}
}


void	initialize_session(t_session *session)
{
	session->tokens = 0;
	session->operators = 0;
	session->pipes = 0;
	session->readfrom = 0;
	session->commands = 0;
	session->writeto = 0;
	session->status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_session	session;

	(void)argc;
	(void)argv;
	session.menvp = setup_menvp(envp);
	initialize_session(&session);
	initialize_signals();
	setup_cd(&session.cd, session.menvp);
	read_evaluate_print_loop(&session);
	free_cd(&session.cd);
	clear(session.menvp);
	return (0);
}
