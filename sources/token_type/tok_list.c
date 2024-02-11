/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:21:22 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/11 00:32:16 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../include/read.h"

t_token	*tok_create(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->cmd = NULL;
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

void tok_remove(t_token *head, t_token *to_remove)
{
	t_token *tmp;

	if (!head || !to_remove)
		return;
	if (head == to_remove)
		return;
	else
	{
		tmp = head;
		while (tmp->next)
		{
			if (tmp->next == to_remove)
			{
				tmp->next = to_remove->next;
				free(to_remove->value);
				if (to_remove->cmd)
					free_table(to_remove->cmd);
				free(to_remove);
				return;
			}
			else
				tmp = tmp->next;
		}
	}

}

t_token	*tok_free_list(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		if (token->cmd)
			free_table(token->cmd);
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
