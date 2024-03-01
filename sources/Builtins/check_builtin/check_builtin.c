/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:11:15 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/29 15:11:06 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

int	check_builtin(t_session *session, int taskn)
{
	char	*builtins[8];
	int		i;

	if (session->commands[taskn][0])
	{
		i = 0;
		builtins[0] = "ourecho";
		builtins[1] = "cd";
		builtins[2] = "pwd";
		builtins[3] = "export";
		builtins[4] = "unset";
		builtins[5] = "env";
		builtins[6] = "exit";
		builtins[7] = NULL;
		while (builtins[i])
		{
			if (!ft_strncmp(session->commands[taskn][0],
				builtins[i], ft_strlen(builtins[i]) + 1))
				return (i + 1);
			i++;
		}
	}
	return (0);
}

void	exec_builtin(t_session *session, char **menvp, int taskn, int builtin)
{
	(void)menvp;
	if (builtin == 2)
		change_dir(&session->cd, session->commands[taskn][1]);
	else if (builtin == 3)
		mpwd();
	else if (builtin == 6)
		menvp(session->menvp);

}
