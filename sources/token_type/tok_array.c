/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:21:05 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/11 02:08:24 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../include/read.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	tok_free_array(t_token *tokens, int i)
{
	while (--i >= 0)
	{
		free(tokens[i].value);
	}
	free(tokens);
}

void	distinguish_cmd_arg(t_token *tokens)
{
	int	i;
	int		cmd;

	i = 0;
	cmd = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == STD && cmd == 0)
			cmd = 1;
		else if (tokens[i].type == STD && cmd == 1)
			tokens[i].type = ARG;
		else if (tokens[i].type > ARG)
			cmd = 0;
		i++;
	}
}

t_token	*tok_create_array(char **split)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(sizeof(t_token) * (split_size(split) + 1));
	if (!tokens)
		return (NULL);
	tokens[split_size(split)].value = 0;
	i = 0;
	while (split[i])
	{
		tokens[i].value = (char *)malloc(sizeof(char)
				* (ft_strlen(split[i]) + 1));
		if (!tokens[i].value)
		{
			tok_free_array(tokens, i);
			return (NULL);
		}
		ft_strlcpy(tokens[i].value, split[i], ft_strlen(split[i]) + 1);
		set_token_type(&tokens[i]);
		i++;
	}
	distinguish_cmd_arg(tokens);
	i = -1;
	while (split[++i])
		printf("token: %s, type: %d\n", tokens[i].value, tokens[i].type);
	return (tokens);
}
