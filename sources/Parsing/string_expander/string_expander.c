/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:43:13 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/18 20:00:52 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"


static int	is_parenthesis(char c)
{
	if (c == '(' || c == ')')
		return (1);
	return (0);
}

static int	special_char(char c)
{
	if (c == '&' || c == '|' || c == '<'|| c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

static int	expanded_size(char *str)
{
	int	i;
	int	qt;
	int	qts;
	int	size;

	i = -1;
	qt = 0;
	qts = 0;
	size = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !(qts % 2))
			qt++;
		if (str[i] == '\"' && !(qt % 2))
			qts++;
		size++;
		if (special_char(str[i + 1]) && (is_parenthesis(str[i + 1])
			|| str[i + 1] != str[i]) && !(qt % 2) && !(qts % 2))
			size++;
		if (special_char(str[i]) && (is_parenthesis(str[i])
			|| str[i + 1] != str[i]) && !(qt % 2) && !(qts % 2))
			size++;
	}
	return (size);
}

static char	*string_transfer(char *exp, char *str)
{
	int	i;
	int	j;
	int	qt;
	int	qts;

	i = -1;
	j = 0;
	qt = 0;
	qts = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !(qts % 2))
			qt++;
		if (str[i] == '\"' && !(qt % 2))
			qts++;
		exp[j++] = str[i];
		if (special_char(str[i + 1]) && (is_parenthesis(str[i + 1])
			|| str[i + 1] != str[i]) && !(qt % 2) && !(qts % 2))
			exp[j++] = ' ';
		if (special_char(str[i]) && (is_parenthesis(str[i])
			|| str[i + 1] != str[i]) && !(qt % 2) && !(qts % 2))
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
	string = expanded;
	return (expanded);
}
