/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:47:46 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/20 11:47:57 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/read.h"
#include "../../include/quote_split.h"
#include "../../include/token.h"
#include "../../include/executer.h"

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

t_token	*tokenize(char *line, char **envp)
{
	char	**split;
	t_token	*tokens;

	if (check_analyzer(line))
		return (0);
	if (ambient_variable_expansion(&line, envp))
		return (0);
	if (expand_and_contract(&line))
		return (0);
	if (handle_quotes(line, &split))
		return (0);
	tokens = tok_create_array(split);
	if (!tokens)
		perror("**tokens alloc failed.\n");
	free_table(split);
	return (tokens);
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
