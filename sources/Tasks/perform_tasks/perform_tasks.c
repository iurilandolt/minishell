/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_tasks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:58:22 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/26 12:27:14 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

void	task(char **envp, t_session *session, int taskn)
{
	int	writefd;
	
	writefd = prepare_writefds(session, taskn);
	perform_redirects(session, taskn, writefd);
	close_opened_fds(session, writefd);
	session->commands[taskn][0] = validate_bin_path(envp, cmd[0]);
	link_cmd_codes(session->commands[taskn][0]);
	
}

void	perform_task(char **envp, t_session *session, int taskn)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		task(envp, session, taskn);
}

void	perform_tasks(char **envp, t_session *session)
{
	int	i;
	int	on;
	int	status;
	
	i = 0;
	on = 0;
	while (i < session->ntasks)
	{
		while (on == 0 || (i + on < session->ntasks
			&& session->operators[i + on - 1].token->type == PIPE))
			perform_task(envp, session, i + on++);
		i += on;
		while (on--)
			wait(&status);
		if (session->operators[i - 1].token->type == SAND 
            		&& !((status & 0xff00) >> 8))
			i += session->operators[i - 1].flag;
		else if (session->operators[i - 1].token->type == OR 
            		&& ((status & 0xff00) >> 8))
			i += session->operators[i - 1].flag;		
	}
}
