/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:42:13 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/15 17:08:28 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../include/read.h"

//add strlen check for safety?
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
	else if (ft_strncmp(token->value, "||", 2) == 0)
		token->type = OR;
	else if (ft_strncmp(token->value, "|", 1) == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->value, "&", 1) == 0)
		token->type = SAND;
	else if (ft_strncmp(token->value, "(", 1) == 0)
		token->type = PRTS;
	else if (ft_strncmp(token->value, ")", 1) == 0)
		token->type = PRTS;
	else
		token->type = STD;
}

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
		else if (tmp->type > STD)
			cmd = 0;
		tmp = tmp->next;
	}
}

void	tok_contract_cmd(t_token *head)
{
	t_token	*tmp;
	t_token	*dest;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == STD)
		{
			dest = tmp;
			tmp = tmp->next;
			while (tmp && tmp->type <= ARG)
			{
				if (tmp->type == ARG)
				{
					dest->value = ft_strjoin(dest->value, " ");
					dest->value = ft_strjoin(dest->value, tmp->value);
					tmp = tok_remove(head, tmp);
				}
				tmp = tmp->next;
			}
			dest->cmd = ft_split(dest->value, ' ');
		}
		else
			tmp = tmp->next;
	}
}
