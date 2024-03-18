/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:46:37 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/15 17:27:15 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtins.h"
#include "../../../../include/executer.h"
#include "../../../../include/read.h"


static int valid_exit_arg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while(str[i])
	{
		if (!isdigit(str[i]))
			return(0);
		i++;
	}
	return (1);
}

void	m_exit(t_session *session, int taskn)
{
	int	value;

	value = 0;
	if (!valid_exit_arg(session->commands[taskn][1])) // leaks
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("exit: numeric argument required", 2);
		rl_clear_history();
		free_args(session->commands[taskn]);
		free_session(session);
		exit(2);
	}
	if (split_size(session->commands[taskn]) > 2) // leaks
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("exit: too many arguments", 2);
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