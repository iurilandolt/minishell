/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chgdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:57 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/24 17:48:09 by rlandolt         ###   ########.fr       */
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
	free(cd->home);
	free(cd->pwd);
	free(cd->oldpwd);
}
