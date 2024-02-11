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

void	tokenize(char *line, char **envp)
{
	char	**split;
	t_token	*tokens;

	if (check_analyzer(line))
		return ;
	if (ambient_variable_expansion(&line, envp))
		return ;
	if (expand_and_contract(&line))
		return ;
	if (handle_quotes(line, &split))
		return ;
	tokens = tok_create_array(split);
	if (!tokens)
		perror("**tokens alloc failed.\n");
	tok_free_array(tokens, split_size(split));
	free_table(split);
}

void	tokenize_list(char *line, char **envp)
{
	char	**split;
	t_token	*tokens;

	if (check_analyzer(line))
		return ;
	if (ambient_variable_expansion(&line, envp))
		return ;
	if (expand_and_contract(&line))
		return ;
	if (handle_quotes(line, &split))
		return ;
	tokens = tok_create_list(split);
	tok_expand_cmd(tokens);
	tok_contract_cmd(tokens);
	print_token_list(tokens);
	if (!tokens)
		write(1, "\0", 1);
	tok_free_list(tokens);
	free_table(split);
}

void	repl(char **envp)
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
		//tokenize(line, envp);
		tokenize_list(line, envp);
		if (line && ft_strlen(line) > 0)
			add_history(line);
		free(line);
		line = readline("<MiniShell> ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	repl(envp);
	return (0);
}
