/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   received_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:59:40 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/19 11:52:37 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

void	received_signal(int signum)
{
	if (signum == SIGINT && g_shell_signal == -2)
	{
		write(1, "\n", 1);
		close(0);
	}
	if (signum == SIGINT && g_shell_signal >= 0)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_shell_signal = signum;
}
