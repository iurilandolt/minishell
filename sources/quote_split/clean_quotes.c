/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:50 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/06 12:02:35 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/quote_split.h"

static void	count_quotes(char *str, int *i, int *qt, int *qts)
{
	*i = -1;
	*qt = 0;
	*qts = 0;
	while (str[++(*i)])
	{
		if (str[*i] == '\'' && (*i == 0 || str[*i - 1] != '\\'))
			(*qt)++;
		if (str[*i] == '\"' && (*i == 0 || str[*i - 1] != '\\'))
			(*qts)++;
	}
}

static char	*allocate_for_clean_word(int i, int qt, int qts)
{
	char	*word;

	word = malloc(i - qt - qts + 1);
	if (!word)
		return (0);
	word[i - qt - qts] = 0;
	return (word);
}

static void	transfer_word(char *str, char *word)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] != '\'' && str[i] != '\"') || (i != 0 && str[i - 1] == '\\'))
			word[j++] = str[i];
	}
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}

char	**clean_quotes(char **table)
{
	int		i;
	int		j;
	int		qt;
	int		qts;
	char	*word;

	i = -1;
	while (table[++i])
	{
		count_quotes(table[i], &j, &qt, &qts);
		word = allocate_for_clean_word(j, qt, qts);
		if (!word)
		{
			perror("malloc = 0");
			free_table(table);
			return (0);
		}
		transfer_word(table[i], word);
		free(table[i]);
		table[i] = word;
	}
	return (table);
}
