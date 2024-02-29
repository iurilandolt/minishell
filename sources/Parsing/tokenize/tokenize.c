/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:47:46 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/25 15:17:02 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"

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

void	print_tokens(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value)
		printf("token: %s, type: %d\n", tokens[i].value, tokens[i].type);
}

t_token	*tokenize(char *line)
{
	char	**split;
	t_token	*tokens;

	if (check_analyzer(line))
		return (0);
	if (expand_and_contract(&line))
		return (0);
	if (handle_quotes(line, &split))
		return (0);
	tokens = tok_create_array(split);
	if (!tokens)
		perror("**tokens alloc failed.\n");
	free_table(split);
	if (tokens_check(tokens))
		return (tok_free_array(tokens));
	print_tokens(tokens);
	return (tokens);
}

