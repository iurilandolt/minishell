/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_writefds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:37:39 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/27 13:44:18 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

int	correct_pipe(t_session *session, int taskn)
{
	if (session->operators[taskn].token->type == PIPE)
		return (session->operators[taskn].flag);
	return (session->operators[taskn + session->operators[taskn].flag].flag);
}

int	prepare_writefds(t_session *session, int taskn)
{
	int	i;
	int	writefd;

	i = -1;
	writefd = 0;
	while (session->writeto[taskn][++i].value
		&& session->writeto[taskn][i].type < PIPE)
	{
		if (session->writeto[taskn][i].type == RED_OUT)
			writefd = open(&session->writeto[taskn][i].value[1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (session->writeto[taskn][i].type == RED_APP)
			writefd = open(&session->writeto[taskn][i].value[2],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (writefd == -1)
			perror(&session->writeto[taskn][++i].value[1]);
		if (session->writeto[taskn][i + 1].value
			&& session->writeto[taskn][i + 1].type < PIPE
			&& close(writefd))
			perror(0);
	}
	if (session->writeto[taskn][0].value
				&& session->writeto[taskn][0].type == PIPE)
		writefd = session->pipes[correct_pipe(session, taskn)][1];
	return (writefd);
}
