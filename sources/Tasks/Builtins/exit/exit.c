/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:46:37 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/18 20:05:23 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtins.h"
#include "../../../../include/executer.h"
#include "../../../../include/read.h"

static int	valid_exit_arg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	m_exit(t_session *session, int taskn)
{
	int	value;

	value = 0;
	if (!valid_exit_arg(session->commands[taskn][1]))
	{
		ft_putendl_fd("exit\nexit: numeric argument required", 2);
		rl_clear_history();
		free_args(session->commands[taskn]);
		free_session(session);
		exit(2);
	}
	if (split_size(session->commands[taskn]) > 2)
	{
		ft_putendl_fd("exit\nexit: too many arguments", 2);
		session->status = 1 << 8;
		return ;
	}
	if (session->commands[taskn][1])
		value = ft_atoi(session->commands[taskn][1]);
	value = (char)value;
	rl_clear_history();
	free_args(session->commands[taskn]);
	free_session(session);
	exit(value);
}
