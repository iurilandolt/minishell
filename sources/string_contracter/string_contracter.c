/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_contracter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:43:00 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/06 13:44:18 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	contracted_size(char *str)
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
		size++;
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			qt++;
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			qts++;
		if ((str[i] == '<' || str[i] == '>') 
			&& str[i + 1] == ' ' && str[i - 1] != '\\')
			size--;
		if (str[i] == ' ' && (!i || str[i - 1] == ' ') 
			&& !(qt % 2) && !(qts % 2))
			size--;
	}
	return (size);
}

static char	*string_transfer(char *con, char *str)
{
	int		i;
	int		j;
	int		qt;
	int		qts;

	i = -1;
	j = 0;
	qt = 0;
	qts = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			qt++;
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			qts++;
		if (i && str[i] == ' ' && (str[i - 1] == '<' || str[i - 1] == '>')
			&& (i < 2 || str[i - 2] != '\\'))
			continue ;
		if (str[i] == ' ' && (!i || str[i - 1] == ' ') 
			&& !(qt % 2) && !(qts % 2))
			continue ;
		con[j++] = str[i];
	}
	return (con);
}

char	*string_contracter(char *string)
{
	int		size;
	char	*contracted;

	size = contracted_size(string);
	contracted = malloc(size + 1);
	if (!contracted)
		return (0);
	contracted[size] = 0;
	contracted = string_transfer(contracted, string);
	free(string);
	return (contracted);
}
