/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/22 18:57:00 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/quote_split.h"
#include "../include/token.h"
#include "../include/executer.h"

static void	free_table_n(void **table, int ntasks)
{
	int	i;
	
	i = -1;
	while (++i < ntasks)
		free(table[i]);
	free(table);
}

int	free_all(t_all *all)
{
	tok_free_array(all->tokens);
	if (all->operators)
		free(all->operators);
	if (all->pipes)
		free(all->pipes);
	if (all->readfrom)
		free_table_n((void **)all->readfrom, all->ntasks);
	if (all->commands)
		free_table_n((void **)all->commands, all->ntasks);
	if (all->writeto)
		free_table_n((void **)all->writeto, all->ntasks);
	return (0);
}

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

int	process_line(char *line, char **envp)
{
	t_all	all;

	all.tokens = tokenize(line, envp);
	if (!all.tokens)
		return (0);
	all.ntasks = number_of_tasks(all.tokens);
	all.operators = operator_rules(all.tokens);
	if (!all.operators)
		return (free_all(&all));
	all.pipes = create_pipes(all.operators);
	if (!all.pipes)
		return (free_all(&all));
	all.readfrom = obtain_read_documents(all.tokens, all.pipes, all.ntasks);
	if (!all.readfrom)
		return (free_all(&all));
	all.commands = obtain_commands(envp, all.tokens, all.ntasks);
	if (!all.commands)
		return (free_all(&all));
	all.writeto = obtain_write_documents(all.tokens, all.ntasks);
	if (!all.writeto)
		return (free_all(&all));
	print_all(&all);
	//perform_tasks(all);
	return (free_all(&all));
}

void	read_evaluate_print_loop(char **envp)
{
	char	*line;

	line = readline("<MiniShell> ");
	while (line)
	{
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			rl_clear_history();
			break ;
		}
		process_line(line, envp);
		if (ft_strlen(line) > 0)
			add_history(line);
		free(line);
		line = readline("<MiniShell> ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	read_evaluate_print_loop(envp);
	return (0);
}
