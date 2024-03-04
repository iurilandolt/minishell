/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/04 23:09:21 by rlandolt         ###   ########.fr       */
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

int	is_validchar(char c)
{
	char	*valid = "*.:/_-=@+!"; // %&?{}[]()~^$#
	int		i;

	i = 0;
	while (valid[i])
	{
		if (c == valid[i])
			return (1);
		i++;
	}
	if (is_alphanum(c))
		return (1);
	return (0);
}

int is_valid_env_format(const char *str)
{
	int	i;

	if (!str || *str == '\0' || !is_alpha(str[0])) // add _
		return 0;
	i = 0;
	while(str[i] && is_alphanum(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	if(str[i] == '+')
		i++;
	if(str[i] != '=')
		return (0);
	i++;
	if (!is_validchar(str[i]) && str[i] != '\0')
		return (0);
	while (is_validchar(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	m_export(char ***menvp, char *value) // int fd
{
	int		i;

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
		printf("-> %d\n", is_valid_env_format(value));
		//parse for lookup, return char **
		//define operation, return int?
		// add, replace or concat?
	}
}

void	m_unset(char ***menvp, char *value) // int fd
{
	int		i;

	if (!value)
		return ;
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
