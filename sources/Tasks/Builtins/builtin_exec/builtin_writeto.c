/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_writeto.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:11:52 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/20 22:24:09 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtins.h"
#include "../../../../include/executer.h"
#include "../../../../include/read.h"

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
	while (token[++i].value && taskn)
	{
		if (token[i].type >= PIPE)
			taskn--;
	}
	return (&token[i]);
}

static int	open_writefd(t_session *session, t_token *token, int oldwritefd)
{
	int		writefd;
	char	*filename;

	writefd = 0;
	filename = token->value;
	ambient_variable_expansion(session, &filename, 0);
	clean_quotes(&filename, 1);
	if (oldwritefd)
		close(oldwritefd);
	if (!filename[1 + (token->type == RED_APP)]
		&& token->value[1 + (token->type == RED_APP)] == '$')
	{
		ft_putstr_fd(&token->value[1 + (token->type == RED_APP)], 2);
		ft_putendl_fd(": ambiguous redirect", 2);
	}
	if (token->type == RED_OUT)
		writefd = open(&filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->type == RED_APP)
		writefd = open(&filename[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (writefd == -1 && token->value[1 + (token->type == RED_APP)] != '$')
		perror(&filename[1 + (token->type == RED_APP)]);
	if (filename)
		free(filename);
	return (writefd);
}

int	open_close(t_session *session, char *filename)
{
	int	fd;

	ambient_variable_expansion(session, &filename, 0);
	clean_quotes(&filename, 1);
	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		session->status = 1;
		if (filename)
			return (perror(filename), free(filename), 1);
		else
			return (perror(filename), 1);
	}
	if (filename)
		free(filename);
	close(fd);
	return (0);
}

int	open_builtin_taskfiles(t_session *session, int taskn)
{
	int		i;
	int		j;
	int		writefd;
	t_token	*token;

	i = -1;
	j = 0;
	writefd = 0;
	token = startfrom(session->tokens, taskn);
	if (token[i + 1].type == PIPE && token[++i].value)
		j++;
	while (token[++i].value && token[i].type < PIPE)
	{
		if (token[i].type == RED_IN && open_close(session, &token[i].value[1]))
			return (-1);
		if (token[i].type == RED_OUT || token[i].type == RED_APP)
			writefd = open_writefd(session, &token[i], writefd);
		if (writefd == -1)
			return (-1);
	}
	if (writefd == 0 && session->writeto[taskn][0].value
		&& session->writeto[taskn][0].type == PIPE)
		writefd = session->pipes[correct_pipe(session, taskn)][1];
	return (writefd);
}
