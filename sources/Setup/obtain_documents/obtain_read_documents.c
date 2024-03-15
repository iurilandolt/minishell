/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_read_documents.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:15 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 14:50:04 by rcastelo         ###   ########.fr       */
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

int	open_here_doc(char *delimiter, int status, char **menvp)
{
	int	i;
	char	*line;
	int	here_doc_pipe[2];

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
		ambient_variable_expansion(status, &line, menvp);
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

int	here_doc(char *delimiter, int *status, char **menvp)
{
	int	fd;
	int	original_stdin;

	shell_signal = -2;
	original_stdin = dup(0);
	if (signal(SIGINT, received_signal) == (void *)-1)
		perror("signal");
	fd = open_here_doc(delimiter, *status, menvp);
	if (shell_signal == SIGINT)
	{
		*status = 130 << 8;
		if (dup2(original_stdin, 0) == -1)
			perror(0);
	}
	close(original_stdin);
	shell_signal = 0;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
        perror("signal not default");
	return (fd);
}

int	*get_read_documents(int (**pipefd)[2], int *status, char **menvp, t_token *tokens)
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
			readfds[j++] = here_doc(&tokens[i].value[2], status, menvp);
		if (tokens[i].type == HERE_DOC && readfds[j - 1] == -1)
			return (free(readfds), (void *)0);
	}
	return (readfds);
}

int	**obtain_read_documents(t_token *tokens, int (*pipefd)[2], t_session *session, int *status)
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
			readfrom[++j] = get_read_documents(&pipefd, status, session->menvp,
				&tokens[i + (tokens[i].type > PIPE)]);
		if ((i == 0 || tokens[i].type >= PIPE) && !readfrom[j])
			return (free(readfrom), (int **)0);
	}
	return (readfrom);
}
