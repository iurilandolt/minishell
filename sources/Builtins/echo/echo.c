/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:08:56 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/06 12:08:57 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

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

char	*add_new_line(char **print)
{
	int	i;
	char	*newprint;
	
	i = 0;
	while ((*print)[i])
		i++;
	newprint = malloc(i + 2);
	if (!newprint)
		return (perror(0), (void *)0);
	newprint[i + 1] = 0;
	i = -1;
	while ((*print)[++i])
		newprint[i] = (*print)[i];
	newprint[i] = '\n';
	free(*print);
	return (newprint); 
}

char	*join_array(char **table)
{
	int	i;
	int	j;
	int	k;
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
	*(string) = 0;
	return (string - k - i);	
}

void	echo(char **cmd)
{
	int	i;
	char	nl;
	char	*print;
	
	i = 0;
	cmd++;
	nl = new_line_option(&cmd);
	print = join_array(cmd);
	if (nl)
		print = add_new_line(&print);
	while (print[i])
		i++;
	write(1, print, i);
	free(print);
}
