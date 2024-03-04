/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_levels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:30:08 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/04 14:58:56 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

void	allocate_environments(t_session *session, int *envlvl, char **menvp)
{
	int	i;
	int	maxlvl;

	i = -1;
	maxlvl = 0;
	while (++i < session->ntasks)
	{
		if (envlvl[i] > maxlvl)
			maxlvl = envlvl[i];
	}
	session->menvp = malloc((maxlvl + 1) * sizeof(char **));
	if (!session->menvp)
		return (perror(0));
	session->menvp[0] = menvp;
	i = 0;
	while (++i <= maxlvl)
		session->menvp[i] = 0;
}

int	*environment_levels(t_session *session, t_token *tokens, char **menvp)
{
	int	i;
	int	j;
	int	k;
	int	*envlvl;

	i = -1;
	j = 0;
	k = 0;
	envlvl = malloc(sizeof(int) * session->ntasks);
	if (!envlvl)
		return (perror(0), (void *)0);
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE)
			j++;
		if (tokens[i].type == PRTS && tokens[i].value[0] == '(')
			k++;
		if (tokens[i].type == PRTS && tokens[i].value[0] == '('
			&& tokens[i - 2].type == PRTS && tokens[i - 2].value[0] == ')')
			k = -k;
		envlvl[j] = k;
		if (tokens[i].type == PRTS && tokens[i].value[0] == ')')
			k = -(k < 0) * k + k * (k > 0) - 1;
	}
	return (allocate_environments(session, envlvl, menvp), envlvl);
}
