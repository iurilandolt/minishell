/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:50 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/11 02:04:14 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/quote_split.h"

static void	count_quotes(char *str, int *i, t_qt *qt, int *bar)
{
	*i = -1;
	qt->qt = 0;
	qt->qts = 0;
	*bar = 0;
	while (str[++(*i)])
	{
		if (str[*i] == '\'' && (*i == 0 || str[*i - 1] != '\\')
			&& !(qt->qts % 2))
			(qt->qt)++;
		if (str[*i] == '\"' && (*i == 0 || str[*i - 1] != '\\')
			&& !(qt->qt % 2))
			(qt->qts)++;
		if (str[*i] == '\\' && (*i == 0 || str[*i - 1] != '\\'))
			(*bar)++;
	}
}

static char	*allocate_for_clean_word(int i, int qt, int qts, int bar)
{
	char	*word;

	word = malloc(i - qt - qts - bar + 1);
	if (!word)
		return (0);
	word[i - qt - qts - bar] = 0;
	return (word);
}

static void	transfer_word(char *str, char *word)
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
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			qt++;
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			qts++;
		if ((!(str[i] == '\'' && !(qts % 2)) && !(str[i] == '\"' && !(qt % 2))
			 && !(str[i] == '\\')) || (i != 0 && str[i - 1] == '\\'))
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
	int		bar;
	t_qt	qt;
	char	*word;

	i = -1;
	while (table[++i])
	{
		count_quotes(table[i], &j, &qt, &bar);
		word = allocate_for_clean_word(j, qt.qt, qt.qts, bar);
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
