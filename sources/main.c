/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/25 13:00:52 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/token.h"
#include "../include/executer.h"
#include "../include/builtins.h"

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

int	process_line(t_session *session, char *line, char **envp)
{
	session->tokens = tokenize(line, envp);
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
	session->commands = obtain_commands(envp, session->tokens, session->ntasks);
	if (!session->commands)
		return (free_session(session));
	session->writeto = obtain_write_documents(session->tokens, session->ntasks);
	if (!session->writeto)
		return (free_session(session));
	print_session(session);
	//perform_tasks(envp, session);
	return (free_session(session));

}

void	read_evaluate_print_loop(t_session *session, char **envp)
{
	char	*line;

	line = readline("<Minishell> ");
	while (line)
	{
		if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) == 4)
		{
			free(line);
			rl_clear_history();
			break ;
		}
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			process_line(session, line, envp);
		}
		free(line);
		line = readline("<Minishell> ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_session	session;
	t_cd		cd;

	(void)argc;
	(void)argv;
	setup_cd(&cd, envp);
	read_evaluate_print_loop(&session, envp);
	return (0);
}
