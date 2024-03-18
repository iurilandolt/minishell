/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_read_documents.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:15 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 15:45:53 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

int	number_of_ins(t_token *tokens)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	if (tokens[i].type == PIPE && tokens[i++].type)
		number++;
	while (tokens[i].value && tokens[i].type < PIPE)
	{
		if (tokens[i].type == RED_IN || tokens[i].type == HERE_DOC)
			number++;
		i++;
	}
	return (number);
}

int	open_here_doc(t_session *session, char *delimiter, char flag)
{
	int		i;
	int		here_doc_pipe[2];
	char	*line;

	if (pipe(here_doc_pipe) == -1)
		return (perror(0), -1);
	while (1)
	{
		line = readline("heredoc> ");
		if (shell_signal == SIGINT)
			return (close(here_doc_pipe[0]), close(here_doc_pipe[1]), -1);
		if (!line)
			return (printf("heredoc ended by ^D (wanted '%s')\n", delimiter),
				close(here_doc_pipe[1]), here_doc_pipe[0]);
		if (!flag)
			ambient_variable_expansion(session, &line, 1);
		i = 0;
		while (line && line[i])
			i++;
		if (i > 0 && !ft_strncmp(line, delimiter, INT_MAX))
			return (free(line), close(here_doc_pipe[1]), here_doc_pipe[0]);
		write(here_doc_pipe[1], line, i);
		write(here_doc_pipe[1], "\n", 1);
		free(line);
	}
}

int	here_doc(t_session *session, char *delimiter)
{
	int		i;
	int		fd;
	int		original_stdin;
	char	quote;

	i = -1;
	shell_signal = -2;
	original_stdin = dup(0);
	if (original_stdin == -1 || signal(SIGINT, received_signal) == SIG_ERR)
		perror("dup and/or signal");
	while (i == -1 || (delimiter[i] && delimiter[i] != '\"'))
		quote = delimiter[i++ + 1];
	clean_quotes(&delimiter, 0);
	fd = open_here_doc(session, delimiter, quote);
	if (shell_signal == SIGINT)
	{
		session->status = 130 << 8;
		if (dup2(original_stdin, 0) == -1)
			perror(0);
	}
	close(original_stdin);
	shell_signal = 0;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("signal not default");
	return (free(delimiter), fd);
}

int	*get_read_documents(int (**pipefd)[2], t_session *session, t_token *tokens)
{
	int	i;
	int	j;
	int	*readfds;

	i = number_of_ins(tokens);
	readfds = malloc((i + 1) * sizeof(int));
	if (!readfds)
		return (perror(0), (void *)0);
	readfds[i] = 0;
	while (i--)
		readfds[i] = -1;
	j = 0;
	if (tokens[i + 1].type == PIPE && tokens[++i].value)
		readfds[j++] = (*(*pipefd)++)[0];
	while (tokens[++i].value && tokens[i].type < PIPE)
	{
		if (tokens[i].type == RED_IN)
			j++;
		else if (tokens[i].type == HERE_DOC)
			readfds[j++] = here_doc(session, &tokens[i].value[2]);
		if (tokens[i].type == HERE_DOC && readfds[j - 1] == -1)
			return (free(readfds), (void *)0);
	}
	return (readfds);
}

int	**obtain_read_documents(t_token *tokens, int (*pipefd)[2],
		t_session *session)
{
	int	i;
	int	j;
	int	**readfrom;

	readfrom = malloc(session->ntasks * sizeof(int *));
	if (!readfrom)
		return (perror(0), (void *)0);
	i = -1;
	while (++i < session->ntasks)
		readfrom[i] = 0;
	i = -1;
	j = -1;
	while (tokens[++i].value)
	{
		if (i == 0 || tokens[i].type >= PIPE)
			readfrom[++j] = get_read_documents(&pipefd, session,
					&tokens[i + (tokens[i].type > PIPE)]);
		if ((i == 0 || tokens[i].type >= PIPE) && !readfrom[j])
			return (free(readfrom), (int **)0);
	}
	return (readfrom);
}
