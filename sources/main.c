/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/05 12:07:56 by rlandolt         ###   ########.fr       */
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

int	process_line(t_session *session, char *line, char ***menvp)
{
	session->tokens = tokenize(line);
	if (!session->tokens)
		return (0);
	session->ntasks = number_of_tasks(session->tokens);
	session->operators = operator_rules(session->tokens);
	if (!session->operators)
		return (free_session(session, 0));
	session->pipes = create_pipes(session->operators);
	if (!session->pipes)
		return (free_session(session, 0));
	session->readfrom = obtain_read_documents(session->tokens,
			session->pipes, session->ntasks);
	if (!session->readfrom)
		return (free_session(session, 0));
	session->commands = obtain_commands(session->tokens, session->ntasks);
	if (!session->commands)
		return (free_session(session, 0));
	session->writeto = obtain_write_documents(session->tokens, session->ntasks);
	if (!session->writeto)
		return (free_session(session, 0));
	session->envlvl = environment_levels(session, session->tokens, *menvp);
	if (!session->envlvl)
		return (free_session(session, 0));
	print_session(session);
	perform_tasks(session);
	*menvp = session->menvp[0];
	return (free_session(session, 0));
}

void	read_evaluate_print_loop(t_session *session, char ***menvp)
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
			process_line(session, line, menvp);
		}
		free(line);
		line = readline("<Minishell> ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**menvp;
	t_session	session;

	(void)argc;
	(void)argv;
	menvp = setup_menvp(envp);
	//initialize session with 0's
	setup_cd(&session.cd, menvp);
	read_evaluate_print_loop(&session, &menvp);
	free_cd(&session.cd);
	clear(menvp);
	return (0);
}
