/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:44:27 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 13:26:41 by rcastelo         ###   ########.fr       */
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
	{
		if (table[i])
			free(table[i]);
	}
	free(table);
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
		free_table_n((void **)session->commands, session->ntasks);
	if (session->writeto)
		free_table_n((void **)session->writeto, session->ntasks);
	if (session->line)
		free(session->line);
	if (session->p_ids)
		free(session->p_ids);
	return (0);
}
