/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/06 11:59:11 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/quote_split.h"

void	debug_input(char *line, char **split)
{
	int	i;
	(void)line;
	printf("in: %s\n", line);
	line = string_expander(line);
	split = quote_split(line, ' ');
	split = clean_quotes(split);
	free(line);
	i = 0;
	while (split[i])
	{
		printf("out :%s\n", split[i]);
		i++;
	}
	free_table(split);
}

void	repl(void)
{
	char	*line;
	char	**split;

	line = readline("<MiniShell> ");
	split = NULL;
	while (line)
	{
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			rl_clear_history();
			break ;
		}
		debug_input(line, split);
		if (line && ft_strlen(line) > 0)
			add_history(line);
		free(line);
		line = readline("$MiniShell> ");
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	repl();
	return (0);
}
