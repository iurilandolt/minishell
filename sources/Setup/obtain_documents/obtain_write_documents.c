/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_write_documents.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:05:40 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/18 19:59:19 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

int	number_of_write_documents(t_token *tokens)
{
	int	i;
	int	number;

	i = -1;
	number = 0;
	while (tokens[++i].value && tokens[i].type < PIPE)
	{
		if (tokens[i].type == RED_OUT || tokens[i].type == RED_APP)
			number++;
	}
	if (tokens[i].value && tokens[i].type == PIPE)
		number++;
	while (tokens[i].value && tokens[i].type != 6 && tokens[i].value[0] != ')')
		i++;
	if (tokens[i].value && tokens[i].type == PRTS && tokens[i + 1].value
		&& tokens[i + 1].type == PIPE)
		number++;
	return (number);
}

t_token	*get_write_documents(t_token *tokens)
{
	int		i;
	int		j;
	int		number;
	t_token	*redout;

	i = -1;
	j = 0;
	number = number_of_write_documents(tokens);
	redout = malloc((number + 1) * sizeof(t_token));
	if (!redout)
		return (perror(0), (void *)0);
	redout[number].value = 0;
	while (tokens[++i].value && tokens[i].type < PIPE)
	{
		if (tokens[i].type == RED_OUT || tokens[i].type == RED_APP)
			redout[j++] = tokens[i];
	}
	if (tokens[i].value && tokens[i].type == PIPE)
		redout[j++] = tokens[i];
	while (tokens[i].value && tokens[i].type != 6 && tokens[i].value[0] != ')')
		i++;
	if (tokens[i].value && tokens[i].type == PRTS && tokens[i + 1].value
		&& tokens[i + 1].type == PIPE)
		redout[j++] = tokens[i + 1];
	return (redout);
}

t_token	**obtain_write_documents(t_token *tokens, int ntasks)
{
	int		i;
	int		j;
	t_token	**writeto;

	writeto = malloc(ntasks * sizeof(t_token *));
	if (!writeto)
		return (perror(0), (void *)0);
	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (i == 0 || tokens[i].type >= PIPE)
			writeto[j++] = get_write_documents(&tokens[i + 1]);
	}
	return (writeto);
}
