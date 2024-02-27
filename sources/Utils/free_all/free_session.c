/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:44:27 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/26 16:17:34 by rlandolt         ###   ########.fr       */
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

	i = -1;
	while (++i < session->ntasks)
	{
		if (session->commands[i][0])
			free(session->commands[i][0]);
		if (session->commands[i])
			free(session->commands[i]);
	}
	free(session->commands);
}

int	free_session(t_session *session)
{
	tok_free_array(session->tokens);
	if (session->operators)
		free(session->operators);
	if (session->pipes)
		free(session->pipes);
	if (session->readfrom)
		free_table_n((void **)session->readfrom, session->ntasks);
	if (session->commands)
		//free_session_commands(session);
	if (session->writeto)
		free_table_n((void **)session->writeto, session->ntasks);
	return (0);
}
