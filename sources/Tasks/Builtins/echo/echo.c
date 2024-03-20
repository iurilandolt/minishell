/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:08:56 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/19 17:43:35 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtins.h"
#include "../../../../include/executer.h"
#include "../../../../include/read.h"

char	new_line_option(char ***cmd)
{
	int	i;
	int	nl;

	nl = 1;
	while ((**cmd) && (**cmd)[0] == '-' && (**cmd)[1])
	{
		i = 0;
		while ((**cmd)[++i])
		{
			if ((**cmd)[i] != 'n')
				return (nl);
		}
		nl = 0;
		(*cmd)++;
	}
	return (nl);
}

char	*join_array(char **table)
{
	int		i;
	int		j;
	int		k;
	char	*string;

	i = -1;
	k = 0;
	while (table[++i])
	{
		j = -1;
		while (table[i][++j])
			k++;
	}
	string = malloc(k + i + 1);
	if (!string)
		return (perror(0), (void *)0);
	while (*table)
	{
		j = -1;
		while ((*table)[++j] || !table++)
			*(string++) = (*table)[j];
		*(string++) = ' ';
	}
	*(string - (i != 0)) = 0;
	return (string - k - i);
}

void	echo(char **cmd, int *status)
{
	int		i;
	char	nl;
	char	*print;

	cmd++;
	nl = new_line_option(&cmd);
	print = join_array(cmd);
	if (!print)
	{
		*status = 2;
		return ;
	}
	i = 0;
	while (print[i])
		i++;
	if (nl)
		write(1, print, i);
	if (nl)
		write(1, "\n", 1);
	else
		write(1, print, i);
	free(print);
}
