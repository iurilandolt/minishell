/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_read_documents.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:15 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/11 17:02:16 by rcastelo         ###   ########.fr       */
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

int	open_here_doc(char *delimiter)
{
	int	i;
	char	*line;
	int	here_doc_pipe[2];
	
	if (pipe(here_doc_pipe) == -1)
		return (perror(0), -1);
	while (1)
	{
		line = readline("heredoc> ");
		i = 0;
		while (line && line[i])
			i++;
		if (shell_signal == SIGINT)
			return (close(here_doc_pipe[0]), close(here_doc_pipe[1]), -1);
		if (i == 0)
			return (free(line), close(here_doc_pipe[1]),
				printf("heredoc ended by ^D (wanted '%s')\n", delimiter),
				here_doc_pipe[0]);
		if (i > 1 && !ft_strncmp(line, delimiter, i - 2)
			&& !ft_strncmp(&line[i - 1], "\n", 1))
			return (free(line), close(here_doc_pipe[1]), here_doc_pipe[0]);
		write(here_doc_pipe[1], line, i);
		free(line);
	}
}

int	here_doc(char *delimiter)
{
	int	fd;
	struct sigaction sigint;
	
	sigint.sa_handler = received_signal;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
		perror("sigaction");
	rl_getc_function = getc;	
	fd = open_here_doc(delimiter);
	shell_signal = 0;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
        perror("signal not default");
	return (fd);
}

int	*get_read_documents(t_token *tokens, int (**pipefd)[2])
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
			readfds[j++] = here_doc(&tokens[i].value[2]);
		if (tokens[i].type == HERE_DOC && readfds[j - 1] == -1)
			return (free(readfds), (void *)0);
	}
	return (readfds);
}

int	**obtain_read_documents(t_token *tokens, int (*pipefd)[2], int ntasks)
{
	int	i;
	int	j;
	int	**readfrom;

	readfrom = malloc(ntasks * sizeof(int *));
	if (!readfrom)
		return (perror(0), (void *)0);
	i = -1;
	while (++i < ntasks)
		readfrom[i] = 0;
	i = -1;
	j = -1;
	while (tokens[++i].value)
	{
		if (i == 0 || tokens[i].type >= PIPE)
			readfrom[++j] = get_read_documents(
				&tokens[i + (tokens[i].type > PIPE)], &pipefd);
		if ((i == 0 || tokens[i].type >= PIPE) && !readfrom[j])
			return (free(readfrom), (int **)0);
	}
	return (readfrom);
}
