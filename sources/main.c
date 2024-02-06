/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:54:35 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/06 17:59:21 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read.h"
#include "../include/quote_split.h"
#include "../include/token.h"

int	expand_and_contract(char **line)
{
	*line = string_expander(*line);
	*line = string_contracter(*line);
	if (!*line)
	{
		perror("**expand_and_contract failed.\n");
		return (1);
	}
	return (0);
}

int	handle_quotes(char *line, char ***split)
{
	*split = quote_split(line, ' ');
	free(line);
	*split = clean_quotes(*split);
	if (!*split)
	{
		perror("**handle_quotes failed.\n");
		return (1);
	}
	return (0);
}

void	tokenize(char *line)
{
	char	**split;
	t_token	*tokens;

	if (check_analyzer(line))
		return ;
	if (expand_and_contract(&line))
		return ;
	if (handle_quotes(line, &split))
		return ;
	tokens = gen_tokens(split);
	if (!tokens)
		perror("**tokens alloc failed.\n");
	free_tokens(tokens, split_size(split));
	free_table(split);

}

void	repl(void)
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
		tokenize(line);
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
