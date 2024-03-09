/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:40:44 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/09 18:39:07 by rlandolt         ###   ########.fr       */
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
