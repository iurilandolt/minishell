/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:57:52 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/11 17:20:14 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

void    initialize_signals(void)
{
    struct sigaction sigint;
    struct sigaction sigquit;
	
	sigint.sa_handler = received_signal;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
		perror("sigaction");
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
		perror("sigaction");
	shell_signal = 0;
	rl_getc_function = getc;
}