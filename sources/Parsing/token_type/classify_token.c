/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:42:13 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/25 15:18:16 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"

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

