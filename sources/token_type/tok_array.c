/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:21:05 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/10 19:21:15 by rlandolt         ###   ########.fr       */
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

t_token *tok_create_array(char **split)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(sizeof(t_token) * (split_size(split)));
	if (!tokens)
		return (NULL);
	i = 0;
	while (split[i])
	{
		tokens[i].value = (char *)malloc(sizeof(char) * (ft_strlen(split[i]) + 1));
		if (!tokens[i].value)
		{
			tok_free_array(tokens, i);
			return (NULL);
		}
		ft_strlcpy(tokens[i].value, split[i], ft_strlen(split[i]) + 1);
		set_token_type(&tokens[i]);
		printf("token: %s, type: %d\n", tokens[i].value, tokens[i].type);
		i++;
	}
	return (tokens);
}
