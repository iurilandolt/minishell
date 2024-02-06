/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/06 16:05:44 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/quote_split.h"
#include "../include/token.h"

void	debug_input(char *line, char **split)
{
	int		size;
	t_token	**tokens;
	line = string_expander(line);
	line = string_contracter(line);
	split = quote_split(line, ' ');
	split = clean_quotes(split);
	size = split_size(split);
	printf("size: %d\n", size);
	free(line);
	tokens = gen_tokens(split);
	if (!tokens)
		perror("**tokens alloc failed.\n");
	free_table(split);
	free_tokens(tokens, size);
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
		line = readline("<MiniShell> ");
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	repl();
	return (0);
}
