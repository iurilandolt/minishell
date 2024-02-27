/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_tasks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:58:22 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/26 17:19:34 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

void	execute_task(char **cmd, char **envp, t_session *session)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		perror("** execve failed.\n");
		free_session(session);
		exit(EXIT_FAILURE);
	}
}

void	task(char **envp, t_session *session, int taskn)
{
	int	writefd;

	writefd = prepare_writefds(session, taskn);
	perform_redirects(session, taskn, writefd);
	close_opened_fds(session, writefd);
	session->commands[taskn][0] = validate_bin_path(envp, session->commands[taskn][0]);
	link_cmd_codes(session->commands[taskn][0]);
	execute_task(session->commands[taskn], envp, session);
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
		if (i > 1 && session->operators[i - 2].token->type == SAND
            		&& !((status & 0xff00) >> 8))
			i += session->operators[i - 2].flag;
		else if (i > 1 && session->operators[i - 2].token->type == OR
            		&& ((status & 0xff00) >> 8))
			i += session->operators[i - 2].flag;
	}
}
