/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:39:15 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/22 18:18:04 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/quote_split.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

void	print_command(char **command)
{
	int	i;
	
	i  = -1;
	if (command[0])
		printf("command:\n");
	while (command[++i])
		printf("\tcmd[%i]: %s\n", i, command[i]);
}

void	print_readfrom(int *readfd)
{
	int	i;
	
	i  = -1;
	if (readfd[0])
		printf("readfrom:\n");
	while (readfd[++i])
		printf("\tfd[%i]: %i\n", i, readfd[i]);
}

void	print_writeto(t_token *tokens)
{
	int	i;
	
	i  = -1;
	if (tokens[0].value)
		printf("writeto:\n");
	while (tokens[++i].value)
		printf("\tvalue: %s; type: %i\n", tokens[i].value, tokens[i].type);
}

void	print_operator(t_operator operator)
{
	if (operator.token)
	{
		printf("operator:\n");
		printf("\tvalue: %s; type: %i\n",operator.token->value, operator.token->type);
		printf("\tflag: %i\n", operator.flag);
	}
}

void	print_all(t_all *all)
{
	int	i;
	
	i = -1;
	while (++i < all->ntasks)
	{
		printf("\nTask %i\n", i);
		print_command(all->commands[i]);
		print_readfrom(all->readfrom[i]);
		print_writeto(all->writeto[i]);
		print_operator(all->operators[i]);
	}
}
