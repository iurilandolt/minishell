/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:58:53 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/05 12:34:17 by rlandolt         ###   ########.fr       */
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

int	menvp_lookup(char *value, char **menvp)
{
	int	i;

	i = 0;
	while (menvp[i])
	{
		if (!ft_strncmp(menvp[i], value, ft_strlen(value))
			&& (menvp[i][ft_strlen(value)] == '='
			|| menvp[i][ft_strlen(value)] == '\0'))
		{
			printf("lookup found %s ->\n", menvp[i]);
			return (i);
		}
		i++;
	}
	return (-1);
}

char **export_to_menvp(char *add, char **menvp)
{
	char	**new;
	int		size;
	int		i;

	size = split_size(menvp);
	new = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (menvp[i])
	{
		new[i] = ft_strdup(menvp[i]);
		if (!new[i])
			return(clear(new));
		i++;
	}
	new[i] = ft_strdup(add);
	if (!new[i])
		return(clear(new));
	new[i + 1] = NULL;
	clear(menvp);
	return(new);
}

char **unset_from_menvp(char *del, char **menvp)
{
	char	**new;
	int		size;
	int		i;
	int		j;

	size = split_size(menvp);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	j =	0;
	while (menvp[i])
	{
		if (!ft_strncmp(menvp[i], del, ft_strlen(del))
			&& (menvp[i][ft_strlen(del)] == '=' || menvp[i][ft_strlen(del)] == '\0'))
		{
			printf("unset found %s ->\n", menvp[i]);
			i++;
		}
		else
		{
			new[j] = ft_strdup(menvp[i]);
			if (!new[j])
				return(clear(new));
			j++;
			i++;
		}
	}
	new[j] = NULL;
	clear(menvp);
	return(new);
}
