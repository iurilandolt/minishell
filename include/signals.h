/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:59 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/18 19:53:02 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	shell_signal;

void	main_signals(int status);
void	received_signal(int signum);
void	task_signals(void);
void	ignore_signals(void);

#endif
