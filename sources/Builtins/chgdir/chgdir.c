/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chgdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:57 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/29 16:11:44 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

void	set_home_directory(t_cd *cd, char **menvp)
{
	int	i;

	i = -1;
	cd->home = NULL;
	while (menvp[++i])
	{
		if (ft_strncmp(menvp[i], "HOME=", 5) == 0)
		{
			cd->home = ft_strdup(menvp[i] + 5);
			break ;
		}
	}
}

void	set_current_directory(t_cd *cd, char **menvp)
{
	int	i;

	i = -1;
	cd->pwd = NULL;
	while (menvp[++i])
	{
		if (ft_strncmp(menvp[i], "PWD=", 4) == 0)
		{
			cd->pwd = getcwd(NULL, 0);
			break ;
		}
	}
}

void	set_old_directory(t_cd *cd, char **menvp)
{
	int	i;

	i = -1;
	cd->oldpwd = NULL;
	while (menvp[++i])
	{
		if (ft_strncmp(menvp[i], "OLDPWD=", 7) == 0)
		{
			cd->oldpwd = ft_strdup(menvp[i] + 7);
			break ;
		}
	}
}

void	setup_cd(t_cd *cd, char **menvp)
{
	set_home_directory(cd, menvp);
	set_current_directory(cd, menvp);
	set_old_directory(cd, menvp);
	printf("home: %s\n", cd->home);
	printf("pwd: %s\n", cd->pwd);
	printf("oldpwd: %s\n", cd->oldpwd);
}

void free_cd(t_cd *cd)
{
	free(cd->home);
	free(cd->pwd);
	free(cd->oldpwd);
}

void mpwd(void)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
}

void	cd_oldpwd(t_cd *cd)
{
	DIR *dir;
	char *tmp;

	if (!cd->oldpwd)
	{
		printf("Minishell doesn't know where you've been.\n");
		return ;
	}
	dir = opendir(cd->oldpwd);
	if (dir != 0)
	{
		tmp = getcwd(NULL, 0);
		chdir(cd->oldpwd);
		free(cd->oldpwd);
		cd->oldpwd = tmp;
		closedir(dir);
	}
}

void	cd_path(t_cd *cd, char *path, DIR *dir)
{
	free(cd->oldpwd);
	cd->oldpwd = getcwd(NULL, 0);
	chdir(path);
	free(cd->pwd);
	cd->pwd = getcwd(NULL, 0);
	closedir(dir);
}

void	change_dir(t_cd *cd, char *path)
{
	DIR		*dir;

	if (!path)
	{
		if (!cd->home)
		{
			printf("Minishell is homeless.\n");
			return ;
		}
		chdir(cd->home);
		return ;
	}
	if (path[0] == '-' && path[1] == '\0')
	{
		cd_oldpwd(cd);
		return ;
	}
	dir = opendir(path);
	if (dir != 0)
	{
		cd_path(cd, path, dir);
		return ;
	}
	printf("cd: %s: Not a directory\n", path);
}
