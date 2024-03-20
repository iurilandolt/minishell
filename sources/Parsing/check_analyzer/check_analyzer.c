/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:53:05 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/20 22:21:37 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"

int	check_closure(char *string)
{
	int	i;
	int	qt;
	int	qts;
	int	opener;

	i = -1;
	qt = 0;
	qts = 0;
	opener = 0;
	while (string[++i])
	{
		if (string[i] == '\'' && !(qts % 2))
			qt++;
		if (string[i] == '\"' && !(qt % 2))
			qts++;
		if (opener < 0)
			return (1);
		if (string[i] == '(' && !(qt % 2) && !(qts % 2))
			opener++;
		if (string[i] == ')' && !(qt % 2) && !(qts % 2))
			opener--;
	}
	if (opener != 0)
		return (1);
	return (0);
}

int	check_openers(char *string, int i)
{
	int	j;
	int	qt;
	int	qts;

	qt = 0;
	qts = 0;
	while (--i >= 0)
	{
		if (string[i] == '\'' && !(qts % 2))
			qt++;
		if (string[i] == '\"' && !(qt % 2))
			qts++;
		j = 1;
		if (string[i] == '(' && !(qt % 2) && !(qts % 2))
		{
			while (i - j > 0 && string[i - j] == ' ')
				j++;
			if (i - j > 0 && (string[i - j] != '&' && string[i - j] != '|'
					&& string[i - j] != '(' && string[i - j]))
				return (1);
		}
	}
	return (0);
}

int	check_closers(char *string)
{
	int	i;
	int	j;
	int	qt;
	int	qts;

	i = -1;
	qt = 0;
	qts = 0;
	while (string[++i])
	{
		if (string[i] == '\'' && !(qts % 2))
			qt++;
		if (string[i] == '\"' && !(qt % 2))
			qts++;
		j = 1;
		if (string[i] == ')' && !(qt % 2) && !(qts % 2))
		{
			while (string[i + j] == ' ')
				j++;
			if (string[i + j] != '&' && string[i + j] != '|'
				&& string[i + j] != ')' && string[i + j])
				return (1);
		}
	}
	return (0);
}

int	check_parenthesis(char *string)
{
	if (check_closure(string))
		return (1);
	if (check_openers(string, ft_strlen(string)))
		return (1);
	if (check_closers(string))
		return (1);
	return (0);
}

int	check_analyzer(char *string)
{
	int	i;
	int	qt;
	int	qts;

	i = -1;
	qt = 0;
	qts = 0;
	if (check_parenthesis(string))
		return (write(2, "Syntax Error\n", 13), 1);
	while (string[++i])
	{
		if (string[i] == '\'' && !(qts % 2))
			qt++;
		if (string[i] == '\"' && !(qt % 2))
			qts++;
		if (string[i] == '\\' && !(qt % 2) && !(qts % 2))
			return (write(2, "Syntax Error\n", 13), 1);
		if (string[i] == ';' && !(qt % 2) && !(qts % 2))
			return (write(2, "Syntax Error\n", 13), 1);
	}
	if (qt % 2 || qts % 2)
		return (write(2, "Syntax Error\n", 13), 1);
	return (0);
}
