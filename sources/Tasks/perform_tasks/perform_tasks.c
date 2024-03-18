/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_tasks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:58:22 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 18:19:56 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

void	task(t_session *session, int taskn)
{
	int	writefd;

	writefd = open_taskfiles(session, taskn);
	perform_redirects(session, taskn, writefd);
	close_opened_fds(session, writefd);
	if (session->commands[taskn])
	{
		session->commands[taskn][0]
			= validate_bin_path(session->menvp, session->commands[taskn][0]);
		link_cmd_codes(session, taskn, session->commands[taskn][0]);
		if (execve(session->commands[taskn][0],
			session->commands[taskn], session->menvp) == -1)
		{
			perror("** execve failed");
			free_session(session);
			exit(EXIT_FAILURE);
		}
	}
	free_session(session);
	exit(0);
}

void	expand_commands(t_session *session, int taskn)
{
	int	i;

	i = -1;
	while (session->commands[taskn] && session->commands[taskn][++i])
		ambient_variable_expansion(session, &session->commands[taskn][i], 0);
	organize_after_expansion(&session->commands[taskn]);
	i = -1;
	while (session->commands[taskn] && session->commands[taskn][++i])
		clean_quotes(&session->commands[taskn][i], 1);
}

void	perform_task(t_session *session, int taskn)
{
	int	pid;
	int	builtn;

	shell_signal = -1;
	task_signals();
	expand_commands(session, taskn);
	builtn = check_builtin(session, taskn);
	if (builtn > 0)
		builtin_task(session, taskn, builtn);
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror(0));
		else if (pid == 0)
			task(session, taskn);
		session->p_ids[taskn] = pid;
		free_args(session->commands[taskn]);
	}
	ignore_signals();
}

void	close_current_pipes(t_session *session, int taskn, int on)
{
	int	i;
	int	pipen;

	i = -1;
	pipen = 0;
	if (taskn >= session->ntasks - 1
		|| session->operators[taskn].token->type != PIPE)
		return ;
	while (session->tokens[++i].value && taskn)
	{
		if (session->tokens[i].type == PIPE)
			pipen++;
		if (session->tokens[i].type >= PIPE)
			taskn--;
	}
	while (session->tokens[i].value && on)
	{
		if (session->tokens[i].type >= PIPE)
			on--;
		if (session->tokens[i].type == PIPE)
			close(session->pipes[pipen][0]);
		if (session->tokens[i].type == PIPE)
			close(session->pipes[pipen++][1]);
		i++;
	}
}

void	perform_tasks(t_session *session)
{
	int	i;
	int	on;

	i = -1;
	on = 0;
	while (++i < session->ntasks && (!session->status || session->status > 255))
	{
		while (on == 0 || (i + on < session->ntasks
				&& session->operators[i + on - 1].token->type == PIPE))
			perform_task(session, i + on++);
		close_current_pipes(session, i, on);
		while (on && on--)
		{
			if (session->p_ids[i++] != 0)
				waitpid(session->p_ids[i - 1], &session->status, 0);
		}
		main_signals(session->status);
		if (i-- < session->ntasks && ((session->operators[i].token->type == SAND
					&& ((session->status & 0xff00) >> 8))
				|| (session->operators[i].token->type == OR
					&& !((session->status & 0xff00) >> 8))))
			on = session->operators[i].flag;
	}
	if (session->status > 0 && session->status < 256)
		session->status = (session->status + (session->status == 2) * 128) << 8;
}
