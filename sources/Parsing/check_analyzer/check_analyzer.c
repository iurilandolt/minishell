/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:53:05 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/06 17:51:36 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"

int	check_closure(char *string)
{
	int	i;
	int	opener;
	int	closer;
	
	i = -1;
	opener = 0;
	closer = 0;
	while (string[++i])
	{
		if (closer > opener)
			return (1);
		if (string[i] == '(')
			opener++;
		if (string[i] == ')')
			closer++;
	}
	if (opener != closer)
		return (1);
	return (0);
}

int	check_openers(char *string)
{
	int	i;
	int	j;
	
	i = 0;
	while (string[i])
		i++;
	while (--i >= 0)
	{
		j = 1;
		if (string[i] == '(')
		{
			while (i - j > 0 && string[i - j] == ' ')
				j++;
			if (string[i - j] != '&' && string[i - j] != '|'
				&& string[i - j] != '(' && string[i - j])
				return (1);	
		}
	}
	return (0);
}

int	check_closers(char *string)
{
	int	i;
	int	j;
	
	i = -1;
	while (string[++i])
	{
		j = 1;
		if (string[i] == ')')
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
	if (check_openers(string))
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
		return (write(2, "Syntax Error\n", 13));
	while (string[++i])
	{
		if (string[i] == '\'' && (i == 0 || string[i - 1] != '\\'))
			qt++;
		if (string[i] == '\"' && (i == 0 || string[i - 1] != '\\'))
			qts++;
		if (string[i] == '\\' && string[i + 1] == 0)
			return (write(2, "Syntax Error\n", 13));
	}
	if (qt % 2 || qts % 2)
		return (write(2, "Syntax Error\n", 13));
	return (0);
}
