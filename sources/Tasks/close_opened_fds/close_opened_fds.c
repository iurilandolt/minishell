/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_opened_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:27:51 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/27 12:36:10 by rlandolt         ###   ########.fr       */
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
		j = 0;
		while (session->readfrom[i][j])
			j++;	
		if (j > 0 && session->readfrom[i][j - 1] > 0)
			close(session->readfrom[i][j - 1]);
	}
	i = -1;
	while (session->pipes[++i][0])
	{
		close(session->pipes[i][0]);
		close(session->pipes[i][1]);
	}
	if (writefd > 0)
		close(writefd);
}
