/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:21:14 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 18:16:46 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

void    task_signals(void)
{
    struct sigaction sigint;
	struct sigaction sigquit;
	
	sigint.sa_handler = received_signal;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
		perror("sigaction");
	sigquit.sa_handler = received_signal;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
		perror("sigaction");
}
