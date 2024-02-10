/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:42:13 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/10 19:45:19 by rlandolt         ###   ########.fr       */
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
	else if (ft_strncmp(token->value, "|", 1) == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->value, "&", 1) == 0)
		token->type = SAND;
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
		else if (tmp->type != STD)
			cmd = 0;
		tmp = tmp->next;
	}

}

//check if token is of type STD, if it is, and the next token is of type ARG;
// strjoin the two tokens and free the next token, keep doing that while the next token is of type ARG

void	tok_contract_cmd(t_token *tok_ptr)
{
	t_token	*tmp;

	tmp = tok_ptr;
	while (tmp)
	{
		tmp = tmp->next;
	}
}
