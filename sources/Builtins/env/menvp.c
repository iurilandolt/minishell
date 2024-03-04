/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/04 18:29:13 by rlandolt         ###   ########.fr       */
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

char	*transform_for_unset(char *value)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while(value[i])
	{
		if (value[i] == '=' || (value[i] == '=' && value[i + 1] == '+'))
			break;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * i + 1);
	j = 0;
	while(j < i)
	{
		tmp[j] = value[j];
		j++;
	}
	tmp[j] = '\0';
	return(tmp);
}

void	m_export(char ***menvp, char *value) // int fd
{
	int		i;
	char	*tmp;
	//char	*extracted;

	if (!*menvp)
		return ;
	if (!value)
	{
		i = 0;
		while (menvp[0][i])
			printf("declare -x %s\n", menvp[0][i++]); // putstr_fd(str, fd)
	}
	else
	{
		if (export_is_replace(value))
		{
			tmp = transform_for_unset(value);
			printf("value %s will be replaced.\n", value);
			*menvp = unset_from_menvp(tmp, *menvp);
			free(tmp);
		}
		else if(export_is_concat(value))
		{
			printf("value %s will be joined.\n", value);
			return ;
		}
		else if (menvp_has_value(value, *menvp))
			return ;
		*menvp = export_to_menvp(value, *menvp);
		if (!*menvp)
			perror("**export error\n");
	}
}

void	m_unset(char ***menvp, char *value) // int fd
{
	int		i;

	if (!value)
	{
		write(2, "unset: not enough arguments\n", 28); // debug -> delete
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
