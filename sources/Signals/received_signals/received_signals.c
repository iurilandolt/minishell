/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   received_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:59:40 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/13 17:04:08 by rlandolt         ###   ########.fr       */
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
		write(2, "\n<Minishell> ", 13);
	shell_signal = signum;
	if (signum == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
}
