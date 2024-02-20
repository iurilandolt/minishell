/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:55:29 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/20 17:57:26 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/read.h"
#include "../../include/quote_split.h"
#include "../../include/token.h"
#include "../../include/executer.h"

void	clean_pipefd(int (*pipefd)[2], int i)
{
	while (--i >= 0)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	free(pipefd);
}

int	(*create_pipes(t_operator *operators))[2]
{
	int	i;
	int	count;
	int	(*pipefd)[2];
	
	i = -1;
	count = 0;
	while (operators[++i].token)
	{
		if(operators[i].token->type == PIPE)
			count++;
	}
	pipefd = malloc(count * sizeof(int[2]));
	if (!pipefd)
		return (0);
	i = -1;
	while (++i < count)
	{
		if (pipe(pipefd[i]) == -1)
		{
			clean_pipefd(pipefd, i);
			return (0);
		}
	}
	return (pipefd);
}
