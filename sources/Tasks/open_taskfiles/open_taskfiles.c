/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_taskfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:05:16 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/28 16:29:22 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

int	correct_pipe(t_session *session, int taskn)
{
	if (session->operators[taskn].token->type == PIPE)
		return (session->operators[taskn].flag);
	return (session->operators[taskn + session->operators[taskn].flag].flag);
}

static t_token	*startfrom(t_token *token, int taskn)
{
	int	i;
	
	i = -1;
	while (token[++i].value && taskn)
	{
		if (token[i].type >= PIPE)
			taskn--;
	}
	return (&token[i]);
}

static void	open_readfd(t_session *session, int *readfds, t_token *token, int j)
{
	readfds[j] = open(&token->value[1], O_RDONLY, 0644);
	if (readfds[j] == -1)
	{
		perror(&token->value[1]);
		free_session(session, 0);
		exit(1);
	}
}

static int	open_writefd(t_token *token, int oldwritefd)
{
	int	writefd;
	
	if (oldwritefd)
		close(oldwritefd);
	if (token->type == RED_OUT)
	{
		writefd = open(&token->value[1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (writefd == -1)
			perror(&token->value[1]);
	}
	if (token->type == RED_APP)
	{
		writefd = open(&token->value[2],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (writefd == -1)
			perror(&token->value[2]);
	}
	return (writefd);
}

int	open_taskfiles(t_session *session, int taskn)
{
	int	i;
	int	j;
	int	writefd;
	t_token	*token;
	
	i = -1;
	j = 0;
	writefd = 0;
	token = startfrom(session->tokens, taskn);
	if (token[i + 1].type == PIPE && token[++i].value)
		j++;
	while (token[++i].value && token[i].type < PIPE)
	{
		if (token[i].type == HERE_DOC)
			j++;
		if (token[i].type == RED_IN)
			open_readfd(session, session->readfrom[taskn], &token[i], j);
		if (token[i].type == RED_OUT || token[i].type == RED_APP)
			writefd = open_writefd(&token[i], writefd);
	}
	if (writefd == 0 && session->writeto[taskn][0].value
		&& session->writeto[taskn][0].type == PIPE)
		writefd = session->pipes[correct_pipe(session, taskn)][1];
	return (writefd);
}
