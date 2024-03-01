/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/01 12:15:57 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"


void	m_envp(char **menvp)
{
	int	i;

	if (!menvp)
		return ;
	i = 0;
	while (menvp[i])
	{
		if (ft_strchr(menvp[i], '='))
			printf("%s\n", menvp[i]);
		i++;
	}
}

void	m_export(char ***menvp, char *value)
{
	int		i;

	if (!*menvp)
		return ;
	if (!value)
	{
		i = 0;
		while (menvp[0][i])
			printf("declare -x %s\n", menvp[0][i++]);
	}
	else
	{
		*menvp = export_to_menvp(value, *menvp);
		if (!*menvp)
			perror("**export error\n");
	}
}

void	m_unset(char ***menvp, char *value)
{
	int		i;

	if (!value)
	{
		perror("unset: not enough arguments\n");
		return ;
	}
	if (!*menvp)
		return ;
	i = 0;
	while (menvp[0][i])
	{
		if (ft_strncmp(value, menvp[0][i], ft_strlen(value)) == 0 && value[0] != '\0')
		{
			*menvp = unset_from_menvp(value, *menvp);
			if (!*menvp)
				perror("**unset error\n");
			return ;
		}
		i++;
	}
}
