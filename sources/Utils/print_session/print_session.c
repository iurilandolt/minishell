/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_session.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:39:15 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/22 18:18:04 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

void	print_command(char **command)
{
	int	i;

	i = -1;
	if (command)
		printf("command:\n");
	while (command && command[++i])
		printf("\tcmd[%i]: %s\n", i, command[i]);
}

void	print_readfrom(int *readfd)
{
	int	i;

	i = -1;
	if (readfd[0])
		printf("readfrom:\n");
	while (readfd[++i])
	{
		printf("\tfd[%i]: ", i);
		if (readfd[i] > 0)
			printf("%i", readfd[i]);
		printf("\n");
	}
}

void	print_writeto(t_token *tokens)
{
	int	i;

	i = -1;
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
		printf("\tvalue: %s; type: %i\n", operator.token->value, operator.token->type);
		printf("\tflag: %i\n", operator.flag);
	}
}

void	print_environmentn(int	environmentn)
{
	printf("environmentn:\n");
	printf("\tlevel: %i\n", environmentn);
}

void	print_session(t_session *session)
{
	int	i;

	i = -1;
	while (++i < session->ntasks)
	{
		printf("\nTask %i\n", i);
		print_command(session->commands[i]);
		print_readfrom(session->readfrom[i]);
		print_writeto(session->writeto[i]);
		print_operator(session->operators[i]);
		print_environment(session->environmentn[i]);
	}
	printf("\n");
}
