/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/11 00:17:11 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/quote_split.h"
#include "../include/token.h"
#include "../include/executer.h"

int	free_all(t_all *all)
{
	tok_free_array(all->tokens);
	if (all->cmdblocks)
		free_cmdblocks(all->cmdblocks);
	if (all->operators)
		free(all->operators);
	if (all->pipefd)
		free(all->pipefd);
	return (0);
}

int	process_line(char *line, char **envp)
{
	t_all	all;

	all.tokens = tokenize(line, envp);
	if (!all.tokens)
		return (0);
	all.cmdblocks = create_cmdblocks(all.tokens);
	if (!all.cmdblocks)
		return (free_all(&all));
	all.operators = operator_rules(all.tokens);
	if (!all.operators)
		return (free_all(&all));
	all.pipefd = create_pipes(all.operators);
	if (!all.pipefd)
		return (free_all(&all));
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
