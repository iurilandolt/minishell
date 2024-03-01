/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:40:44 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:04 by rlandolt         ###   ########.fr       */
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
