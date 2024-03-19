/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_opened_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:27:51 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/19 13:29:10 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

void	close_opened_fds(t_session *session, int writefd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < session->ntasks)
	{
		j = -1;
		while (session->readfrom[i] && session->readfrom[i][++j])
		{
			if (session->readfrom[i][j] > 0)
				close(session->readfrom[i][j]);
		}
	}
	i = -1;
	while (session->pipes[++i])
	{
		close(session->pipes[i][0]);
		close(session->pipes[i][1]);
	}
	if (writefd > 0)
		close(writefd);
}
