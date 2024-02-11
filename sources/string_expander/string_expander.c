/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:43:13 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/11 02:01:22 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/read.h"

static int	expanded_size(char *str)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		size++;
		if (((str[i] != ' ' && str[i] != '&' && str[i] != '|'
					&& str[i] != '\\' && str[i] != '<' && str[i] != '>')
				|| (i != 0 && str[i - 1] == '\\'))
			&& (str[i + 1] == '&' || str[i + 1] == '|'
				|| str[i + 1] == '<' || str[i + 1] == '>'))
			size++;
		if ((str[i + 1] != ' ' && str[i + 1] != '&' && str[i + 1] != '|'
				&& str[i + 1] != '<' && str[i + 1] != '>')
			&& (str[i] == '&' || str[i] == '|'
				|| str[i] == '<' || str[i] == '>')
			&& (i == 0 || str[i - 1] != '\\'))
			size++;
	}
	return (size);
}

static char	*string_transfer(char *exp, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		exp[j++] = str[i];
		if (((str[i] != ' ' && str[i] != '&' && str[i] != '|'
					&& str[i] != '\\' && str[i] != '<' && str[i] != '>')
				|| (i != 0 && str[i - 1] == '\\'))
			&& (str[i + 1] == '&' || str[i + 1] == '|'
				|| str[i + 1] == '<' || str[i + 1] == '>'))
			exp[j++] = ' ';
		if ((str[i + 1] != ' ' && str[i + 1] != '&' && str[i + 1] != '|'
				&& str[i + 1] != '<' && str[i + 1] != '>')
			&& (str[i] == '&' || str[i] == '|'
				|| str[i] == '<' || str[i] == '>')
			&& (i == 0 || str[i - 1] != '\\'))
			exp[j++] = ' ';
	}
	return (exp);
}

char	*string_expander(char *string)
{
	int		size;
	char	*expanded;

	size = expanded_size(string);
	expanded = malloc(size + 1);
	if (!expanded)
		return (0);
	expanded[size] = 0;
	expanded = string_transfer(expanded, string);
	free(string);
	string = expanded;
	return (expanded);
}
