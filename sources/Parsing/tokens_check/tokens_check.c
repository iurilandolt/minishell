/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:17:55 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/20 22:20:53 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"

static int	special_char_b(char c, char flag)
{
	if (flag && !c)
		return (1);
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	redirect_value(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value)
	{
		if (tokens[i].type == RED_IN && special_char_b(tokens[i].value[1], 1))
			return (write(2, "Syntax Error\n", 13), 1);
		if (tokens[i].type == HERE_DOC && special_char_b(tokens[i].value[2], 1))
			return (write(2, "Syntax Error\n", 13), 1);
		if (tokens[i].type == RED_OUT && special_char_b(tokens[i].value[1], 1))
			return (write(2, "Syntax Error\n", 13), 1);
		if (tokens[i].type == RED_APP && special_char_b(tokens[i].value[2], 1))
			return (write(2, "Syntax Error\n", 13), 1);
	}
	return (0);
}

int	operator_value(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value)
	{
		if (tokens[i].type == PIPE && special_char_b(tokens[i].value[1], 0))
			return (write(2, "Syntax Error\n", 13), 1);
		if (tokens[i].type == SAND && (tokens[i].value[0] != tokens[i].value[1]
				|| special_char_b(tokens[i].value[2], 0)))
			return (write(2, "Syntax Error\n", 13), 1);
		if (tokens[i].type == OR && special_char_b(tokens[i].value[2], 0))
			return (write(2, "Syntax Error\n", 13), 1);
	}
	return (0);
}

int	operator_position(t_token *tokens)
{
	int	i;

	i = -1;
	if (tokens->value && tokens->type >= PIPE)
		return (write(2, "Syntax Error\n", 13), 1);
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE
			&& (tokens[i + 1].value && tokens[i + 1].type >= PIPE))
			return (write(2, "Syntax Error\n", 13), 1);
	}
	if (tokens[--i].type >= PIPE)
		return (write(2, "Syntax Error\n", 13), 1);
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
