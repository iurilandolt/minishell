/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chgdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:57 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/09 18:55:37 by rlandolt         ###   ########.fr       */
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

void	cd_path(t_session *session, char *path)
{
	char	*cwd;
	char	*value;

	// update oldpwd to current dir
	cwd = getcwd(NULL, 0);
	value	= ft_strjoin("OLDPWD=", cwd);
	m_unset(&session->menvp, "OLDPWD");
	m_export(&session->menvp, value);
	free(cwd);
	free(value);
	//move to new dir
	chdir(path);
	//update pwd to current dir
	cwd = getcwd(NULL, 0);
	value	= ft_strjoin("PWD=", cwd);
	m_unset(&session->menvp, "PWD");
	m_export(&session->menvp, value);
	free(cwd);
	free(value);
}

void	cd_oldpwd(t_session *session)
{
	DIR		*dir;
	char	*oldpwd;


	oldpwd = set_directory(OLDPWD, session->menvp);
	if (!oldpwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return ;
	}
	dir = opendir(oldpwd);
	if (dir != 0)
	{
		//cd_path(session, oldpwd);
		chdir(oldpwd);
		closedir(dir);
		mpwd();
		return ;
	}
}

void	change_dir(t_session *session, char *path)
{
	DIR		*dir;
	char	*home;

	if (!path)
	{
		home = set_directory(HOME, session->menvp);
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return ;
		}
		chdir(home);
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
		return ;
	}
	printf("cd: %s: Not a directory\n", path); // replace error msg
}
