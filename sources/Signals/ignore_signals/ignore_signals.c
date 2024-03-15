/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:35:19 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 18:16:39 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

void    ignore_signals(void)
{
    struct sigaction sigint;
	struct sigaction sigquit;

	sigint.sa_handler = SIG_IGN;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
		perror("sigaction");
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
		perror("sigaction");
	shell_signal = 0;
}