/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/19 13:28:33 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/token.h"
#include "../include/executer.h"
#include "../include/builtins.h"
#include "../include/signals.h"

int	g_shell_signal;

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

void	initialize_session(t_session *session)
{
	session->tokens = 0;
	session->operators = 0;
	session->pipes = 0;
	session->readfrom = 0;
	session->commands = 0;
	session->writeto = 0;
	session->p_ids = 0;
}

void	process_line(t_session *session, char *line)
{
	session->tokens = tokenize(line, &session->status);
	if (!session->tokens)
		return (free_session(session));
	session->ntasks = number_of_tasks(session->tokens);
	session->operators = operator_rules(session->tokens);
	if (!session->operators)
		return (free_session(session));
	session->pipes = create_pipes(session->operators);
	if (!session->pipes)
		return (free_session(session));
	session->readfrom = obtain_read_documents(session->tokens,
			session->pipes, session);
	if (!session->readfrom)
		return (free_session(session));
	session->commands = obtain_commands(session->tokens, session->ntasks);
	if (!session->commands)
		return (free_session(session));
	session->writeto = obtain_write_documents(session->tokens, session->ntasks);
	if (!session->writeto)
		return (free_session(session));
	session->p_ids = list_process_ids(session->ntasks);
	if (!session->p_ids)
		return (free_session(session));
	perform_tasks(session);
	return (free_session(session));
}

void	read_evaluate_print_loop(t_session *session)
{
	initialize_session(session);
	session->line = readline("<Minishell> ");
	while (session->line)
	{
		g_shell_signal = 0;
		if (ft_strlen(session->line) > 0)
		{
			add_history(session->line);
			process_line(session, session->line);
		}
		else
			free(session->line);
		initialize_session(session);
		session->line = readline("<Minishell> ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_session	session;

	(void)argc;
	(void)argv;
	main_signals(0);
	session.status = 0;
	session.menvp = setup_menvp(envp);
	update_shlvl(&session);
	read_evaluate_print_loop(&session);
	clear(session.menvp);
	return (0);
}
