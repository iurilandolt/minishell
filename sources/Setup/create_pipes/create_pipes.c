/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:55:29 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/19 13:22:56 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/executer.h"

static void	clean_pipefd(int **pipefd, int i)
{
	while (--i >= 0)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	free(pipefd);
}

int	**create_pipes(t_operator *operators)
{
	int	i;
	int	count;
	int	**pipefd;

	i = -1;
	count = 0;
	while (operators[++i].token)
	{
		if (operators[i].token->type == PIPE)
			count++;
	}
	pipefd = malloc((count + 1) * sizeof(int *));
	if (!pipefd)
		return (perror(0), (void *)0);
	pipefd[count] = 0;
	i = -1;
	while (++i < count)
	{
		pipefd[i] = malloc(2 * sizeof(int));
		if (!pipefd[i])
			return (perror(0), free_table_n((void **)pipefd, i - 1), (int **)0);
	}

	i = -1;
	while (++i < count)
	{
		if (pipe(pipefd[i]) == -1)
			return (perror(0), clean_pipefd(pipefd, i), (int **)0);
	}
	return ((int **)pipefd);
}
