/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/29 22:41:57 by rlandolt         ###   ########.fr       */
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

void	m_envp(char **menvp)
{
	int	i;

	if (!menvp)
		return ;
	i = 0;
	while (menvp[i])
		printf("%s\n", menvp[i++]);
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

	size = split_size(menvp);
	new = (char **)malloc(sizeof(char *) * (size));
	if (!new)
		return (NULL);

	i = 0;
	while (menvp[i])
	{
		if (ft_strncmp(menvp[i], del, ft_strlen(del)) == 0)
			break ;
		new[i] = ft_strdup(menvp[i]);
		i++;
	}
	new[i] = NULL;
	clear(menvp);
	return(new);
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
		}
		i++;
	}
}


/*
void	export_to_menvp(char *add, char **menvp){}

void	unset_from_menvp(char *del, char **menvp){}
*/
