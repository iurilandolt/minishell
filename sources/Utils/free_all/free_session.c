/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:44:27 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/19 15:12:46 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"
#include "../../../include/executer.h"

void	free_args(char **table)
{
	int	i;

	i = -1;
	while (table && table[++i])
		free(table[i]);
}

void	exit_safe(t_session *session, int taskn, int code)
{
	if (session->commands[taskn])
		free_args(session->commands[taskn]);
	free_session(session);
	clear_history();
	clear(session->menvp);
	exit(code);
}

void	free_table_n(void **table, int ntasks)
{
	int	i;

	i = -1;
	while (++i < ntasks)
	{
		if (table[i])
			free(table[i]);
	}
	free(table);
}

void	close_readfrom(int **readfrom, int ntasks)
{
	int	i;
	int	j;

	i = 0;
	while (i < ntasks)
	{
		j = 0;
		while (readfrom[i] && readfrom[i][j] != 0)
		{
			close(readfrom[i][j]);
			j++;
		}
		i++;
	}
}

void	free_session(t_session *session)
{
	if (session->tokens)
		tok_free_array(session->tokens);
	if (session->operators)
		free(session->operators);
	if (session->pipes)
		free_table((char **)session->pipes);
	if (session->readfrom)
	{
		close_readfrom(session->readfrom, session->ntasks);
		free_table_n((void **)session->readfrom, session->ntasks);
	}
	if (session->commands)
		free_table_n((void **)session->commands, session->ntasks);
	if (session->writeto)
		free_table_n((void **)session->writeto, session->ntasks);
	if (session->line)
		free(session->line);
	if (session->p_ids)
		free(session->p_ids);
}
