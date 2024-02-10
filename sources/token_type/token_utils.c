/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 02:43:16 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/10 02:50:08 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../include/read.h"

void	tok_expand_cmd(t_token *head)
{
	t_token	*tmp;
	int		cmd;

	cmd = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == STD && cmd == 0)
			cmd = 1;
		else if (tmp->type == STD && cmd == 1)
			tmp->type = ARG;
		else if (tmp->type != STD)
			cmd = 0;
		tmp = tmp->next;
	}

}

t_token	*tok_create(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->value = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	ft_strlcpy(token->value, str, ft_strlen(str) + 1);
	set_token_type(token);
	return (token);
}

t_token	*tok_free_list(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
	return (NULL);
}

t_token	*tok_create_list(char **split)
{
	t_token	*first;
	t_token	*new;
	t_token	*last;
	int		i;

	i = 0;
	first = NULL;
	while (split[i])
	{
		if (i == 0)
		{
			first = tok_create(split[i]);
			if (!first)
				return (NULL);
			last = first;
		}
		else
		{
			new = tok_create(split[i]);
			if (!new)
				return (tok_free_list(first));
			last->next = new;
			last = new;
		}
		i++;
	}
	return (first);
}

void	print_token_list(t_token *head)
{
	t_token	*token;

	token = head;
	while (token)
	{
		if (!token->value)
			return ;
		printf("token: %s, type: %d\n", token->value, token->type);
		token = token->next;
	}
}
