/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:17:55 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/11 16:13:46 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"

int	redirect_value(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value)
	{
		if (tokens[i].type == RED_IN && !tokens[i].value[1])
			return (write(2, "Syntax Error\n", 13));
		if (tokens[i].type == HERE_DOC && (tokens[i].value[2] == '<'
				|| tokens[i].value[2] == '>' || !tokens[i].value[2]))
			return (write(2, "Syntax Error\n", 13));
		if (tokens[i].type == RED_OUT && !tokens[i].value[1])
			return (write(2, "Syntax Error\n", 13));
		if (tokens[i].type == RED_APP && (tokens[i].value[2] == '>'
				|| tokens[i].value[2] == '<' || !tokens[i].value[2]))
			return (write(2, "Syntax Error\n", 13));
	}
	return (0);
}

int	operator_value(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value)
	{
		if (tokens[i].type == SAND 
			&& ((tokens[i].value[0] != tokens[i].value[1])
				|| (tokens[i].value[1] && tokens[i].value[2])))
			return (write(2, "Syntax Error\n", 13));
		if (tokens[i].type == OR && tokens[i].value[2])
			return (write(2, "Syntax Error\n", 13));
	}
	return (0);
}

int	operator_position(t_token *tokens)
{
	int	i;

	i = -1;
	if (tokens->value && tokens->type >= PIPE)
		return (write(2, "Syntax Error\n", 13));
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE 
			&& (tokens[i + 1].value && tokens[i + 1].type >= PIPE))
			return (write(2, "Syntax Error\n", 13));
	}
	if (tokens[--i].type >= PIPE)
		return (write(2, "Syntax Error\n", 13));
	return (0);
}

int	tokens_check(t_token *tokens)
{
	if (operator_position(tokens))
		return (1);
	if (operator_value(tokens))
		return (1);
	if (redirect_value(tokens))
		return (1);
	return (0);
}
