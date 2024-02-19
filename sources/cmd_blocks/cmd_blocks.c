/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:04:29 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/19 13:05:34 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../include/read.h"

int	count_subtasks(t_token *tokens)
{
	int	i;
	int	count;
	
	i = -1;
	if (!tokens->value)
		return (0);
	count = 1;
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE)
			count++;	
	}
	return (count);
}

int	argument_count(t_token *tokens)
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

char	**concatenate_cmd(t_token *tokens)
{
	int	i;
	int	size;
	char	**cmd;
	
	i = 0;
	size = argument_count(tokens);
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (0);
	cmd[size] = 0;
	while (tokens->value && tokens->type <= ARG)
	{
		if (tokens->type == STD || tokens->type == ARG)
			cmd[i++] = tokens->value;
		tokens++;
	}
	return (cmd);
}

void	fill_cmdblocks(t_cmdblock *cmdblock, t_token *tokens)
{
	int	i;
	
	i = -1;
	while (tokens[++i].value)
	{
		if (tokens[i].type == STD)
			cmdblock->cmd = concatenate_cmd(&tokens[i]);
		if (tokens[i].type <= HERE_DOC && tokens[i].type >= RED_IN)
			cmdblock->redin = &tokens[i];
		if (tokens[i].type <= RED_APP && tokens[i].type >= RED_OUT)
			cmdblock->redout = &tokens[i];
		if (tokens[i].type >= PIPE)
		{
			if (tokens[i].type == PIPE)
				cmdblock->redout = &tokens[i];
			cmdblock++;
			if (tokens[i].type == PIPE)
				cmdblock->redin = &tokens[i];
		}
	}
}

t_cmdblock  *create_cmdblocks(t_token *tokens)
{
	int	i;
	int	block_count;
	t_cmdblock	*cmdblock;
	
	i = -1;
	block_count = count_subtasks(tokens);
	cmdblock = malloc(sizeof(t_cmdblock) * (block_count + 1));
	if (!cmdblock)
		return (NULL);
	cmdblock[block_count].cmd = 0;
	while (cmdblock[++i].cmd)
	{
		cmdblock[i].redin = 0;
		cmdblock[i].redout = 0;
	}
	fill_cmdblocks(cmdblock, tokens);
	return (cmdblock);
}
