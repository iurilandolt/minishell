/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:42:13 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/08 14:43:32 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../include/read.h"

void	set_token_type(t_token *token)
{
	if (!token->value)
		return ;
	else if (ft_strncmp(token->value, ">>", 2) == 0)
		token->type = RED_APP;
	else if (ft_strncmp(token->value, "<<", 2) == 0)
		token->type = HERE_DOC;
	else if (ft_strncmp(token->value, ">", 1) == 0)
		token->type = RED_OUT;
	else if (ft_strncmp(token->value, "<", 1) == 0)
		token->type = RED_IN;
	else if (ft_strncmp(token->value, "|", 1) == 0 || ft_strncmp(token->value, "&", 1) == 0)
		token->type = OPERATOR;
	else if (ft_strncmp(token->value, "$", 1) == 0)
		token->type = EVAR;
	else
		token->type = UNHANDLED;
}

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	free_tokens(t_token *tokens, int i)
{
	while (--i >= 0)
	{
		free(tokens[i].value);
	}
	free(tokens);
}

t_token *gen_tokens(char **split)
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
			free_tokens(tokens, i);
			return (NULL);
		}
		ft_strlcpy(tokens[i].value, split[i], ft_strlen(split[i]) + 1);
		set_token_type(&tokens[i]);
		printf("token: %s, type: %d\n", tokens[i].value, tokens[i].type);
		i++;
	}
	return (tokens);
}
