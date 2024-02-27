/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_read_documents.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:15 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/27 15:23:17 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

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

int	open_file_descriptor(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		perror(filename);
	return (fd);
}

int	open_here_doc(char *delimiter)
{
	int	i;
	char	*line;
	int	here_doc_pipe[2];

	if (pipe(here_doc_pipe) == -1)
	{
		perror(0);
		return (-1);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		i = 0;
		while (line && line[i])
			i++;
		if (!ft_strncmp(line, delimiter, --i - 1)
			&& !ft_strncmp(&line[i], "\n", 1))
			break;
		write(here_doc_pipe[1], line, i);
		write(here_doc_pipe[1], "\n", 1);
		free(line);
	}
	free(line);
	close(here_doc_pipe[1]);
	return (here_doc_pipe[0]);
}

int	*get_read_documents(t_token *tokens, int (**pipefd)[2])
{
	int	i;
	int	j;
	int	number;
	int	*readfds;

	number = number_of_ins(tokens);
	readfds = malloc((number + 1) * sizeof(int));
	if (!readfds)
		return (perror(0), (void *)0);
	readfds[number] = 0;
	i = -1;
	j = 0;
	if (tokens[i + 1].type == PIPE && tokens[++i].value)
		readfds[j++] = (*(*pipefd)++)[0];
	while (tokens[++i].value && tokens[i].type < PIPE)
	{
		if (tokens[i].type == RED_IN)
			readfds[j++] = open_file_descriptor(&tokens[i].value[1]);
		else if (tokens[i].type == HERE_DOC)
			readfds[j++] = open_here_doc(&tokens[i].value[2]);
		if (j > 1 && tokens[i].type <= HERE_DOC && close(readfds[j - 2]))
			perror(0);
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
	}
	return (readfrom);
}
