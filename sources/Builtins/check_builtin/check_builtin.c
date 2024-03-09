/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:11:15 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/09 13:06:17 by rlandolt         ###   ########.fr       */
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

void	exec_builtin(t_session *session, int taskn, int builtin)
{
	int	i;

	i = 1;
	if (builtin == 1)
		echo(session->commands[taskn]);
	if (builtin == 2)
		change_dir(&session->cd, session->commands[taskn][1]);
	else if (builtin == 3)
		mpwd();
	else if (builtin == 4)
	{
		if (!session->commands[taskn][i])
			m_export(&session->menvp, 0);
		while (session->commands[taskn][i])
			m_export(&session->menvp, session->commands[taskn][i++]);
	}
	else if (builtin == 5)
		{
		if (!session->commands[taskn][i])
			m_unset(&session->menvp, 0);
		while (session->commands[taskn][i])
			m_unset(&session->menvp, session->commands[taskn][i++]);
	}
	else if (builtin == 6)
		m_envp(session->menvp);
}

void	forked_builtin(t_session *session, int taskn, int builtn)
{
	int	i;
	int	writefd;

	i = -1;
	writefd = open_taskfiles(session, session->menvp, taskn);
	while (session->commands[taskn] && session->commands[taskn][++i])
	{
		ambient_variable_expansion(session->status, &session->commands[taskn][i], session->menvp);
		clean_quotes(&session->commands[taskn][i]);
	}

	perform_redirects(session, taskn, writefd);
	close_opened_fds(session, writefd);
	exec_builtin(session, taskn, builtn);
	free_args(session->commands[taskn]);
	free_session(session);

	exit(0);
}

void	regular_builtin(t_session *session, int taskn, int builtn)
{
	int	i;
	int	stdout_fd;
	int	writefd;

	i = -1;
	while (session->commands[taskn] && session->commands[taskn][++i])
	{
		ambient_variable_expansion(session->status, &session->commands[taskn][i], session->menvp);
		clean_quotes(&session->commands[taskn][i]);
	}
	writefd = open_builtin_taskfiles(session, session->menvp, taskn);
	if (writefd)
	{
		if ((stdout_fd = dup(1)) == -1)
			perror("dup2");
		if (dup2(writefd, 1) == -1)
			perror("dup2");
		close(writefd);
	}
	exec_builtin(session, taskn, builtn);
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
	}
	else
		regular_builtin(session, taskn, builtn);
}
