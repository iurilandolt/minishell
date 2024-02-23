/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:01:13 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/23 16:01:14 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	perform_redirects(t_session *session, int taskn, int writefd)
{
	int	i;
	
	i = 0;
	while (session->readfrom[taskn][i])
		i++;
	i--;
	if (i >= 0 && session->readfrom[taskn][i] > 0)
	{
		if (dup2(session->readfrom[taskn][i], 0) == -1)
			perror(0);
		close(session->readfrom[taskn][i]);
	}
	if (writefd)
	{
		if (dup2(writefd, 1) == -1)
			perror(0);
		close(writefd);		
	}
}
