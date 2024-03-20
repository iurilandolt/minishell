/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chgdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:57 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/20 13:02:54 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtins.h"
#include "../../../../include/executer.h"
#include "../../../../include/read.h"

void	mpwd(int *status)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
	*status = 0;
}

void	change_dir(t_session *session, char **cmd, int *status)
{
	DIR		*dir;

	if (!cmd[1])
		return (cd_home(session));
	if (cmd[2])
		return (cd_error(cmd[1], " : too many arguments", status));
	if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (cd_oldpwd(session));
	dir = opendir(cmd[1]);
	if (dir != 0)
	{
		cd_path(session, cmd[1]);
		closedir(dir);
		return ;
	}
	cd_error(cmd[1], " : No such file or directory", status);
}
