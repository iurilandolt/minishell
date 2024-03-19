/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:59 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/19 11:52:45 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_shell_signal;

void	main_signals(int status);
void	received_signal(int signum);
void	task_signals(void);
void	ignore_signals(void);

#endif
