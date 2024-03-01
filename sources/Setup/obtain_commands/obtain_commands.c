/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:15:31 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/27 13:40:22 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

static int	argument_count(t_token *tokens)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tokens[i].value && tokens[i].type <= ARG)
	{
		if (tokens[i].type == STD || tokens[i].type == ARG)
			size++;
		i++;
	}
	return (size);
}

static char	**concatenate_cmd(t_token *tokens)
{
	int		i;
	int		size;
	char	**cmd;

	i = 0;
	size = argument_count(tokens);
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
	{
		perror(0);
		return (0);
	}
	cmd[size] = 0;
	while (tokens->value && tokens->type <= ARG)
	{
		if (tokens->type == STD || tokens->type == ARG)
		{
			//tokens->value = expand_tilde(tokens->value);
			cmd[i++] = tokens->value;
		}
		tokens++;
	}
	return (cmd);
}

char	***obtain_commands(t_token *tokens, int ntasks)
{
	int		i;
	int		j;
	char	***commands;

	commands = malloc(ntasks * sizeof(char **));
	if (!commands)
	{
		perror(0);
		return (0);
	}
	i = -1;
	while (++i < ntasks)
		commands[i] = 0;
	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE)
			j++;
		if (tokens[i].type == STD)
			commands[j] = concatenate_cmd(&tokens[i]);
	}
	return (commands);
}
