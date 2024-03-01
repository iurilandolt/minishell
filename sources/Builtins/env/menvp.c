/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/01 00:32:41 by rlandolt         ###   ########.fr       */
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
		printf("%s\n", menvp[i++]);
}

void	m_export(char ***menvp, char *value)
{
	if (!value)
		m_envp(*menvp);
	else
	{
		*menvp = export_to_menvp(value, *menvp);
		if (!*menvp)
			perror("**Export error\n");
	}
}

void	m_unset(char ***menvp, char *value)
{
	int		i;
	char	**target;

	if (!value)
	{
		perror("unset: not enough arguments\n");
		return ;
	}
	target = *menvp;
	if (!target)
		return ;
	i = 0;
	while (target[i])
	{
		if (ft_strncmp(target[i], value, ft_strlen(value)) == 0 && value[0] != '\0')
		{
			printf("found %s\n", value);
			*menvp = unset_from_menvp(value, *menvp);
			if (!*menvp)
				perror("**Unset error\n");
			return ;
		}
		i++;
	}
}


/*
void	export_to_menvp(char *add, char **menvp){}

void	unset_from_menvp(char *del, char **menvp){}
*/
