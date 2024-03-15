/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:29:52 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/14 16:53:08 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

static char *extract_var(char *value)
{
	int		i;
	int		size;
	char	*var;

	if (!value)
		return (NULL);
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

	if (!value)
		return (NULL);
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

static char *extract_value(char *value)
{
	char	*ptr;
	int		size;
	char	*new;

	if (!value)
		return (NULL);
	ptr = value;
	while (*ptr && *ptr != '=')
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	else if (*ptr == '=')
		ptr++;
	size = 0;
	while (ptr[size])
		size++;
	if (size > 0)
	{
		new = (char *)malloc(sizeof(char) * (size + 1));
		if (!new)
			return (NULL);
		ft_strlcpy(new, ptr, size + 1);
		return (new);
	}
	return (NULL);
}

char **parse_for_export(char *value)
{
	char **new;

	new = (char **)malloc(sizeof(char *) * 4);
	if (!new)
		return (NULL);
	new[0] = extract_var(value);
	new[1] = extract_op(value);
	new[2] = extract_value(value);
	new[3] = NULL;
	return (new);
}
