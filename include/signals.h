/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:59 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 16:36:38 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	shell_signal;

void    main_signals(int status);
void	received_signal(int signum);
void    task_signals(void);
void    ignore_signals(void);

#endif
