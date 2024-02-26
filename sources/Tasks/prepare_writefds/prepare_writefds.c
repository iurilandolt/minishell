/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_writefds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:37:39 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/23 15:38:10 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

int	prepare_writefds(t_session *session, int taskn)
{
	int	i;
	int	writefd;
	
	i = -1;
	writefd = 0;
	while (session->writeto[taskn][++i].value 
		&& session->writeto[taskn][i].type < PIPE)
	{
		if (session->writeto[taskn][++i].type == RED_OUT)
			writefd = open(&session->writeto[taskn][++i].value[1], 
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (session->writeto[taskn][++i].type == RED_APP)
			writefd = open(&session->writeto[taskn][++i].value[1], 
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (writefd == -1)
			perror(&session->writeto[taskn][++i].value[1]);
		if (session->writeto[taskn][i + 1].value 
			&& session->writeto[taskn][i + 1].type < PIPE
			&& close(writefd))
			perror(0);
	}
	if (session->writeto[taskn][0].type == PIPE)
		writefd = session->pipes[session->operators[taskn].flag];
	return (writefd);
}
