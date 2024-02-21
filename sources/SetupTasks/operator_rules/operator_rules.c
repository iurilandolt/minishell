/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:38 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/20 14:32:59 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

int	count_operators(t_token *tokens)
{
	int	i;
	int	count;
	
	i = -1;
	count = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE)
			count++;
	}
	return (count);
}

void	and_or_operators(t_token *tokens, t_operator *operator, char bit)
{
	int	i;
	int	j;
	int	prts;
	
	i = 0;
	j = 1;
	prts = 0;
	operator->token = tokens;
	tokens++;
	while (tokens[i].value && (tokens[i].type != OR - bit || prts > 0)
		&& !(tokens[i].type == PIPE && prts < 0))
	{
		if (tokens[i].type == PRTS && tokens[i].value[0] == '(')
			prts++; 
		if (tokens[i].type == PRTS && tokens[i].value[0] == ')')
			prts--; 
		if (tokens[i].type >= PIPE)
			j++;
		i++;
	}
	operator->flag = j;
}

void	assign_operator_codes(t_token *tokens, t_operator *operators)
{
	int	i;
	int	j;
	int	k;
	
	i = -1;
	j = 0;
	k = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE)
		{
			if (tokens[i].type == PIPE)
			{
				operators[j].token = &tokens[i];
				operators[j++].flag = k++;
			}
			if (tokens[i].type == SAND)
				and_or_operators(&tokens[i], &operators[j++], 0);
			if (tokens[i].type == OR)
				and_or_operators(&tokens[i], &operators[j++], 1);
		}
	}
}

void	print_operators(t_operator *operators)
{
	int	i;
	
	i = -1;

	while (operators[++i].token)
	{
		printf("\n");
		printf("op: %s; type: %i\n", operators[i].token->value, operators[i].token->type);
		printf("flag: %i\n", operators[i].flag);
	}
}

t_operator	*operator_rules(t_token *tokens)
{
	int	count;
	t_operator	*operators;

	count = count_operators(tokens);
	operators = malloc((count + 1) * sizeof(t_operator));
	if (!operators)
		return (0);
	operators[count].token = 0;
	assign_operator_codes(tokens, operators);
	print_operators(operators);
	return (operators);
}
