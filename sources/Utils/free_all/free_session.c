/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:44:27 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/27 12:27:00 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"
#include "../../../include/executer.h"

void	free_readfrom(int **readfrom, int ntasks)
{
	int	i;

	i = -1;
	while (++i < ntasks)
		free(readfrom[i]);
	free(readfrom);
}

void	free_table_n(void **table, int ntasks)
{
	int	i;

	i = -1;
	while (++i < ntasks)
		free(table[i]);
	free(table);
}

void	free_session_commands(t_session *session)
{
	int	i;
	int	j;

	i = -1;
	while (++i < session->ntasks)
	{
		j = -1;
		while (session ->commands[i] && session->commands[i][++j])
			free(session->commands[i][j]);
		if (session->commands[i])
			free(session->commands[i]);
	}
	free(session->commands);
}

int	free_session(t_session *session, char flag)
{
	tok_free_array(session->tokens);
	if (session->operators)
		free(session->operators);
	if (session->pipes)
		free(session->pipes);
	if (session->readfrom)
		free_table_n((void **)session->readfrom, session->ntasks);
	if (flag && session->commands)
		free_session_commands(session);
	if (!flag && session->commands)
		free_table_n((void **)session->commands, session->ntasks);
	if (session->writeto)
		free_table_n((void **)session->writeto, session->ntasks);
	if (session->environmentn)
		free(session->environmentn);
	return (0);
}
