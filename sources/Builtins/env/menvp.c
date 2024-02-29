/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/29 15:11:05 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

char **setup_menvp(char **envp)
{
	char	**menvp;
	int		size;
	int		i;

	size = split_size(envp);
	menvp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!menvp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		menvp[i] = ft_strdup(envp[i]);
		if (!menvp[i])
			return(clear(menvp));
		i++;
	}
	menvp[size] = NULL;
	return(menvp);
}

void	menvp(char **menvp)
{
	int	i;

	i = 0;
	while (menvp[i])
		printf("%s\n", menvp[i++]);
}
/*
void	export_to_menvp(char *add, char **menvp){}

void	unset_from_menvp(char *del, char **menvp){}
*/
