/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_after_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:45:22 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/18 22:11:39 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

static int	count_arguments(char **command, int qt, int qts)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (command[++i])
	{
		j = 0;
		if (command[i][0])
			count++;
		while (command[i][j] == ' ')
			j++;
		while (command[i][j])
		{
			if (command[i][j] == '\'' && !(qts % 2))
				qt++;
			if (command[i][j] == '\"' && !(qt % 2))
				qts++;
			if (command[i][j++] == ' ' && command[i][j] != ' '
				&& command[i][j] && !(qt % 2) && !(qts % 2))
				count++;
		}
	}
	return (count);
}

static char	*ft_strdup_n(char *string, int n, int *k, int j)
{
	int		i;
	char	*new;

	new = malloc ((n + 1) * sizeof(char));
	if (!new)
		return (perror(0), (char *)0);
	i = -1;
	while (string[++i] && i < n)
		new[i] = string[i];
	new[n] = 0;
	*k = j;
	return (new);
}

static void	transfer_arguments(char **new, char **command, int qt, int qts)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (command[++i])
	{
		k = 0;
		j = 0;
		while (command[i][j] == ' ')
			j++;
		while (command[i][j])
		{
			if (command[i][j] == '\'' && !(qts % 2))
				qt++;
			if (command[i][j] == '\"' && !(qt % 2))
				qts++;
			if ((command[i][j++] == ' ' && command[i][j] != ' ' && command[i][j]
				&& !(qt % 2) && !(qts % 2)) || !command[i][j])
				*(new++) = ft_strdup_n(&command[i][k],
						j - 1 - k + !command[i][j], &k, j);
		}
	}
}

void	organize_after_expansion(char ***command)
{
	int		i;
	int		count;
	char	**new;

	if (!*command)
		return ;
	count = count_arguments(*command, 0, 0);
	new = malloc((count + 1) * sizeof(char *));
	if (!new)
		return (perror("malloc"));
	new[count] = 0;
	transfer_arguments(new, *command, 0, 0);
	i = -1;
	while ((*command)[++i])
		free((*command)[i]);
	free(*command);
	*command = new;
}
