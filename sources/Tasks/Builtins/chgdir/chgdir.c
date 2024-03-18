/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chgdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:57 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/18 20:08:34 by rlandolt         ###   ########.fr       */
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

void	change_dir(t_session *session, char *path, int *status)
{
	DIR		*dir;

	*status = 0;
	if (!path)
		return (cd_home(session));
	if (path[0] == '-' && path[1] == '\0')
		return (cd_oldpwd(session));
	dir = opendir(path);
	if (dir != 0)
	{
		cd_path(session, path);
		closedir(dir);
		return ;
	}
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("Not a directory.", 2);
	*status = 1;
}
