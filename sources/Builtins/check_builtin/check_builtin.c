/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:11:15 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/15 17:30:32 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

int	check_builtin(t_session *session, int taskn)
{
	char	*builtins[8];
	int		i;

	if (!session->commands[taskn])
		return (0);
	if (session->commands[taskn][0])
	{
		i = 0;
		builtins[0] = "echo";
		builtins[1] = "cd";
		builtins[2] = "pwd";
		builtins[3] = "export";
		builtins[4] = "unset";
		builtins[5] = "env";
		builtins[6] = "exit";
		builtins[7] = NULL;
		while (builtins[i])
		{
			if (!ft_strncmp(session->commands[taskn][0],
				builtins[i], ft_strlen(builtins[i]) + 1))
				return (i + 1);
			i++;
		}
	}
	return (0);
}

void	exec_builtin(t_session *session, char **cmd, int taskn, int builtin)
{
	if (builtin == 1)
		echo(cmd, &session->status);
	if (builtin == 2)
		change_dir(session, *(++cmd), &session->status);
	else if (builtin == 3)
		mpwd(&session->status);
	else if (builtin == 4)
	{
		if (!*(++cmd))
			m_export(&session->status, &session->menvp, 0);
		while (*cmd)
			m_export(&session->status, &session->menvp, *cmd++);
	}
	else if (builtin == 5)
	{
		if (!*(++cmd))
			m_unset(&session->status, &session->menvp, 0);
		while (*cmd)
			m_unset(&session->status, &session->menvp, *cmd++);
	}
	else if (builtin == 6)
		m_envp(&session->status, session->menvp);
	else if (builtin == 7)
		m_exit(session, taskn);
}

void	forked_builtin(t_session *session, int taskn, int builtn)
{
	int	writefd;

	writefd = open_taskfiles(session, taskn);
	perform_redirects(session, taskn, writefd);
	close_opened_fds(session, writefd);
	exec_builtin(session, session->commands[taskn], taskn, builtn);
	free_args(session->commands[taskn]);
	free_session(session);
	exit(session->status);
}

void	regular_builtin(t_session *session, int taskn, int builtn)
{
	int	stdout_fd;
	int	writefd;

	writefd = open_builtin_taskfiles(session, taskn);
	if (writefd)
	{
		stdout_fd = dup(1);
		if (stdout_fd == -1)
			perror("dup");
		if (dup2(writefd, 1) == -1)
			perror("dup2");
		close(writefd);
	}
	exec_builtin(session, session->commands[taskn], taskn, builtn);
	free_args(session->commands[taskn]);
	if (writefd)
	{
		if (dup2(stdout_fd, 1) == -1)
			perror("dup2");
	}
}

void builtin_task(t_session *session, int taskn, int builtn)
{
	int	i;
	pid_t	pid;

	i = 0;
	while(session->writeto[taskn][i].value)
		i++;
	if ((i > 0 && session->writeto[taskn][i - 1].type == PIPE)
		|| (taskn > 0 && session->operators[taskn - 1].token->type == PIPE))
	{
		pid = fork();
		if (pid == -1)
			perror("builtin fork failed.");
		else if (pid == 0)
			forked_builtin(session, taskn, builtn);
		session->p_ids[taskn] = pid;
		free_args(session->commands[taskn]);
	}
	else
		regular_builtin(session, taskn, builtn);
}
