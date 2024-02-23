/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_tasks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:58:22 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/23 13:58:40 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	prepare_writefds(t_session *session, int taskn)
{
	int	i;
	int	write fd;
	
	i = -1;
	while (session->writeto[taskn][++i].value 
		&& session->writeto[taskn][i].type < PIPE)
	if (session->writeto[taskn][0].type == PIPE)
		writefd = session->pipes[session->operator[taskn].flag];
}

void	task(char **envp, t_session *session, int taskn)
{
	int	writefd;
	
	writefd = prepare_writefds(session, taskn);
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
			&& session->operator[i + on - 1].token->type == PIPE))
			perform_task(envp, session, i + on++);
		i += on;
		while (on--)
			wait(&status);
		if (session->operator[i - 1].token->type == SAND && exit_status(status))
			i += session->operator[i - 1].flag;
		else if (session->operator[i - 1].token->type == OR && !exit_status(status))
			i += session->operator[i - 1].flag;		
	}
}
