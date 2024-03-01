/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:35:50 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/01 12:35:51 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

static int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}

char	**correct_environment(t_session *session, int taskn)
{
	if (!taskn || session->envlvl[taskn] == session->envlvl[taskn - 1])
		return (session->menvp[session->envlvl[taskn]];
	else if (session->envlvl[taskn] < 0)
	{
		if (session->menvp[-session->envlvl[taskn]])
			free_table(session->menvp[-session->envlvl[taskn]]);
		session->menvp[-session->envlvl[taskn]] =
			setup_menvp(session->menvp[-session->envlvl[taskn] - 1])
		return (session->menvp[-session->envlvl[taskn]]);
	}
	else if (session->envlvl[taskn] > session->envlvl[taskn - 1])
	{
		session->menvp[session->envlvl[taskn]] =
			setup_menvp(session->menvp[session->envlvl[taskn - 1]])
		return (session->menvp[session->envlvl[taskn]]);
	}
	else if (session->envlvl[taskn] < session->envlvl[taskn - 1])
	{
		if (session->menvp[session->envlvl[taskn - 1]])
			free_table(session->menvp[ft_abs(session->envlvl[taskn - 1])]);	
		return (session->menvp[session->envlvl[taskn]]);
	}
}
