/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/05 00:39:23 by rlandolt         ###   ########.fr       */
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

static char *extract_var(char *value)
{
	int		i;
	int		size;
	char	*var;

	size = 0;
	while (value[size])
	{
		if (value[size] == '+' || value[size] == '=')
			break ;
		size++;
	}
	var = (char *)malloc(sizeof(char) * (size + 1));
	if (!var)
		return (NULL);
	i = 0;
	while (i < size)
	{
		var[i] = value[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

static char *extract_op(char *value)
{
	char	*ptr;

	ptr = value;
	while(*ptr)
	{
		if (*ptr == '+' || *ptr == '=')
			break ;
		ptr++;
	}
	if (*ptr == '\0')
		return (NULL);
	if (*ptr == '=')
		return (ft_strdup("="));
	else if (*ptr == '+' && *++ptr == '=')
		return (ft_strdup("+="));
	return (NULL);
}

char **parse_for_export(char *value)
{
	char **new;

	new = (char **)malloc(sizeof(char *) * 4);
	if (!new)
		return (NULL);

	// new[0] = extract var -> always has one
	new[0] = extract_var(value);
	// new[1] = extract op -> set to NULL if not found
	new[1] = extract_op(value);
	new[2] = NULL;
	new[3] = NULL;

	// new[2] = extract value -> set to NULL if not found or if new[1] is NULL
	// new[3] = NULL

	return (new);
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
		if (is_valid_env_format(value))
		{
			char **parsed = parse_for_export(value);
			i = 0;
			while (parsed[i])
				printf("%s\n", parsed[i++]);
			clear(parsed);
		}
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
