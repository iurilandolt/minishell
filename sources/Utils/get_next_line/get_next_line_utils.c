/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:04:58 by rcastelo          #+#    #+#             */
/*   Updated: 2023/09/27 12:04:59 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_buffer(char *buffer, int buffer_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		buffer[i++] = 0;
	if (buffer[i] == '\n')
		buffer[i++] = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	while (j < buffer_size)
		buffer[j++] = 0;
}

char	assemble_line(char **line, char *buffer)
{
	int		ij[2];
	int		last_char_index;
	char	*new_line;

	ij[0] = 0;
	ij[1] = 0;
	while (*line && (*line)[ij[0]])
		ij[0]++;
	while (buffer[ij[1]] && (!ij[1] || buffer[ij[1] - 1] != '\n'))
		ij[1]++;
	last_char_index = ij[0] + ij[1] - 1;
	new_line = malloc(ij[0] + ij[1] + 1);
	if (!new_line)
		return (-1);
	new_line[ij[0] + ij[1]] = 0;
	while (--ij[1] >= 0)
		new_line[ij[0] + ij[1]] = buffer[ij[1]];
	while (--ij[0] >= 0)
		new_line[ij[0]] = (*line)[ij[0]];
	if (*line)
		free(*line);
	*line = new_line;
	if (last_char_index == -1)
		return (0);
	return ((*line)[last_char_index]);
}
