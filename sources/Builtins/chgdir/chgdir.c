/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chgdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:57 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/13 17:57:46 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

void mpwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
}

void	change_dir(t_session *session, char *path)
{
	DIR		*dir;

	if (!path)
	{
		cd_home(session);
		return ;
	}
	if (path[0] == '-' && path[1] == '\0')
	{
		cd_oldpwd(session);
		return ;
	}
	dir = opendir(path);
	if (dir != 0)
	{
		cd_path(session, path);
		closedir(dir);
		// status = 0?
		return ;
	}
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("Not a directory.", 2);
	// status = 1
}
