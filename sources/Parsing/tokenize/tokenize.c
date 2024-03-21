/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:47:46 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/21 13:04:20 by rcastelo         ###   ########.fr       */
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
	*split = shell_split(line, 0, 0);
	free(line);
	if (!*split)
	{
		perror("**handle_quotes failed.\n");
		return (1);
	}
	if (!**split)
	{
		free_table(*split);
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

t_token	*tokenize(char *line, int *status)
{
	char	**split;
	t_token	*tokens;
	int		curr_status;

	curr_status = *status;
	*status = 2 << 8;
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
	*status = curr_status;
	return (tokens);
}
