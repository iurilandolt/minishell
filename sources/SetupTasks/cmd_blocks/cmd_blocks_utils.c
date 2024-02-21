/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_blocks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:07:21 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/19 17:07:35 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"

void	print_cmdblocks(t_cmdblock *cmdblocks)
{
	int	i;
	
	while (cmdblocks->cmd)
	{
		i = -1;
		printf("\n");
		while (cmdblocks->cmd[++i])
			printf("cmd[%i]: %s\n", i, cmdblocks->cmd[i]);
		if (cmdblocks->redin)
			printf("redin: %s\n", cmdblocks->redin->value);
		if (cmdblocks->redout)
			printf("redout: %s\n", cmdblocks->redout->value);
		cmdblocks++;
	}
}

void	free_cmdblocks(t_cmdblock *cmdblocks)
{
	int	i;
	
	i = -1;
	while (cmdblocks[++i].cmd)
		free(cmdblocks[i].cmd);
	free(cmdblocks);
}
