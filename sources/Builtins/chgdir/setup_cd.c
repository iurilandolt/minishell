/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:40:44 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/14 13:48:34 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

char	*set_directory(t_sysdir dir, char **menvp)
{
	char	*ptr;
	int		i;


	i = -1;
	ptr = NULL;
	while (menvp[++i])
	{
		if (dir == HOME && ft_strncmp(menvp[i], "HOME=", 5) == 0)
			ptr = (menvp[i] + 5);
		else if (dir == PWD && ft_strncmp(menvp[i], "PWD=", 4) == 0)
			ptr = (menvp[i] + 4);
		else if (dir == OLDPWD && ft_strncmp(menvp[i], "OLDPWD=", 7) == 0)
			ptr = (menvp[i] + 7);
		if (ptr)
			return(ptr);
	}
	return(NULL);
}

void	cd_path(t_session *session, char *path)
{
	char	*cwd;
	char	*value;

	cwd = getcwd(NULL, 0);
	value	= ft_strjoin("OLDPWD=", cwd);
	m_export(&session->menvp, value);
	free(cwd);
	free(value);
	chdir(path);
	cwd = getcwd(NULL, 0);
	value	= ft_strjoin("PWD=", cwd);
	m_export(&session->menvp, value);
	free(cwd);
	free(value);
}

void	cd_oldpwd(t_session *session)
{
	DIR		*dir;
	char	*oldpwd;
	char	*buffer;


	oldpwd = set_directory(OLDPWD, session->menvp);
	if (!oldpwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return ;
	}
	dir = opendir(oldpwd);
	if (dir != 0)
	{
		buffer = ft_strdup(oldpwd);
		cd_path(session, buffer);
		closedir(dir);
		free(buffer);
		mpwd(&session->status);
		return ;
	}
}

void	cd_home(t_session *session)
{
	char	*home;
	char	*buffer;


	home = set_directory(HOME, session->menvp);
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return ;
	}
	buffer = ft_strdup(home);
	cd_path(session, buffer);
	free(buffer);
	return ;
}
