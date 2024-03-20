/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_taskfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:05:16 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/20 22:23:04 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

static int	correct_pipe(t_session *session, int taskn)
{
	if (session->operators[taskn].token->type == PIPE)
		return (session->operators[taskn].flag);
	return (session->operators[taskn + session->operators[taskn].flag].flag);
}

static t_token	*startfrom(t_token *token, int taskn)
{
	int	i;

	i = -1;
	if (!taskn)
		return (&token[0]);
	while (taskn && token[++i].value)
	{
		if (token[i].type >= PIPE)
			taskn--;
	}
	if (token[i].type == SAND || token[i].type == OR)
		i++;
	return (&token[i]);
}

static void	open_readfd(t_session *session, int *readfd,
	t_token *token, int taskn)
{
	char	*filename;

	filename = &token->value[1];
	ambient_variable_expansion(session, &filename, 0);
	clean_quotes(&filename, 1);
	*readfd = open(filename, O_RDONLY, 0644);
	if (filename)
		free(filename);
	if (*readfd == -1)
	{
		perror(&token->value[1]);
		close_opened_fds(session, 0);
		exit_safe(session, taskn, 1);
	}
}

static int	open_writefd(t_session *session, t_token *token,
	int writefd, int taskn)
{
	char	*filename;

	filename = token->value;
	ambient_variable_expansion(session, &filename, 0);
	clean_quotes(&filename, 1);
	if (writefd)
		close(writefd);
	if (!filename[1 + (token->type == RED_APP)]
		&& token->value[1 + (token->type == RED_APP)] == '$')
	{
		ft_putstr_fd(&token->value[1 + (token->type == RED_APP)], 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		exit_safe(session, taskn, 1);
	}
	if (token->type == RED_OUT)
		writefd = open(&filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->type == RED_APP)
		writefd = open(&filename[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (writefd == -1)
		perror(&filename[1 + (token->type == RED_APP)]);
	if (filename)
		free(filename);
	if (writefd == -1)
		exit_safe(session, taskn, 1);
	return (writefd);
}

int	open_taskfiles(t_session *session, int taskn)
{
	int			i;
	int			j;
	int			writefd;
	t_token		*token;

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
			open_readfd(session, &session->readfrom[taskn][j++],
				&token[i], taskn);
		if (token[i].type == RED_OUT || token[i].type == RED_APP)
			writefd = open_writefd(session, &token[i], writefd, taskn);
	}
	if (writefd == 0 && session->writeto[taskn][0].value
		&& session->writeto[taskn][0].type == PIPE)
		writefd = session->pipes[correct_pipe(session, taskn)][1];
	return (writefd);
}
