/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chgdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:57 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/28 17:13:39 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

void	set_home_directory(t_cd *cd, char **envp)
{
	int	i;

	i = -1;
	cd->home = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			cd->home = ft_strdup(envp[i] + 5);
			break ;
		}
	}
}

void	set_current_directory(t_cd *cd, char **envp)
{
	int	i;

	i = -1;
	cd->pwd = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			cd->pwd = getcwd(NULL, 0);
			break ;
		}
	}
}

void	set_old_directory(t_cd *cd, char **envp)
{
	int	i;

	i = -1;
	cd->oldpwd = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			cd->oldpwd = ft_strdup(envp[i] + 7);
			break ;
		}
	}
}

void	setup_cd(t_cd *cd, char **envp)
{
	set_home_directory(cd, envp);
	set_current_directory(cd, envp);
	set_old_directory(cd, envp);
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
	dir = opendir(path);
	if (dir != 0)
	{
		chdir(path);
		closedir(dir);
		return ;
	}
	printf("cd: %s: Not a directory\n", path);
}
