/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_tasks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:58:22 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/29 11:46:13 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

void	execute_task(char **cmd, char **envp, t_session *session)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		perror("** execve failed");
		free_session(session, 1);
		exit(EXIT_FAILURE);
	}
}

void	task(char **envp, t_session *session, int taskn)
{
	int	writefd;

	writefd = open_taskfiles(session, taskn);
	perform_redirects(session, taskn, writefd);
	close_opened_fds(session, writefd);
	session->commands[taskn][0]
		= validate_bin_path(envp, session->commands[taskn][0]);
	link_cmd_codes(session->commands[taskn][0]);
	execute_task(session->commands[taskn], envp, session);
}

void	perform_task(char **envp, t_session *session, int taskn)
{
	int	pid;
	int	builtn;

	builtn = check_builtin(session, taskn);
	if (builtn > 0)
	{
		printf("call to builtin %d\n", builtn);
		exec_builtin(session, taskn, builtn);
	}
		else
		{
		pid = fork();
		if (pid == -1)
			return (perror(0));
		else if (pid == 0)
			task(envp, session, taskn);
	}
}

void	close_current_pipe(t_session *session, int taskn)
{
	int	i;
	int	pipen;

	i = 0;
	pipen = 0;
	if (taskn >= session->ntasks - 1
		|| session->operators[taskn].token->type != PIPE)
		return ;
	while (session->tokens[i].value && taskn)
	{
		if (session->tokens[i].type >= PIPE)
			taskn--;
		if (session->tokens[i].type == PIPE)
			pipen++;
		i++;
	}
	close(session->pipes[pipen][1]);
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
		while (on && on--)
		{
			wait(&status);
			close_current_pipe(session, i++);
		}
		if (i < session->ntasks && session->operators[i - 1].token->type == SAND
            		&& ((status & 0xff00) >> 8))
			on += session->operators[i - 1].flag;
		if (i < session->ntasks && session->operators[i - 1].token->type == OR
			&& !((status & 0xff00) >> 8))
			on += session->operators[i - 1].flag;
		while (on && on--)
			close_current_pipe(session, i++);
	}
}
