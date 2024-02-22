/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 23:04:20 by rcastelo          #+#    #+#             */
/*   Updated: 2023/09/26 23:04:50 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

char	*get_next_line(int fd)
{
	int			nread;
	char		last_char;
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	line = 0;
	if (*buffer)
	{
		last_char = assemble_line(&line, buffer);
		update_buffer(buffer, BUFFER_SIZE);
		if (last_char == 10)
			return (line);
	}
	nread = 1;
	while (nread > 0)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		last_char = assemble_line(&line, buffer);
		update_buffer(buffer, BUFFER_SIZE);
		if (last_char == 10 || (nread == 0 && last_char > 0 && *line))
			return (line);
	}
	if (line)
		free(line);
	return (0);
}
