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

#include "../../../include/read.h"
#include "../../../include/executer.h"

static void	clean_pipefd(int (*pipefd)[2], int i)
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
	pipefd = malloc((count + 1) * sizeof(int[2]));
	if (!pipefd)
		return (perror(0), 0);
	pipefd[count][0] = 0;
	i = -1;
	while (++i < count)
	{
		if (pipe(pipefd[i]) == -1)
			return (perror(0), clean_pipefd(pipefd, i), 0);
	}
	return (pipefd);
}
