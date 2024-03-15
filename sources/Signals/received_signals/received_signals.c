/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   received_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:59:40 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 18:06:36 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

void	received_signal(int signum)
{
	if (signum == SIGINT && shell_signal == -2)
	{
		write(1, "\n", 1);
		close(0);
	}
	if (signum == SIGINT && shell_signal == -1)
		write(2, "\n", 1);
	if (signum == SIGINT && shell_signal > -1)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	shell_signal = signum;
}
