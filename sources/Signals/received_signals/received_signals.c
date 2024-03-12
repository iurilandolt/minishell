/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   received_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:59:40 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/11 17:30:07 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"
#include "../../../include/signals.h"

void	received_signal(int signum)
{
	fprintf(stderr, "signum: %i\n", signum);
	shell_signal = signum;
	if (signum == SIGQUIT)
		fprintf(stderr, "Quit (core dumped)\n");
}