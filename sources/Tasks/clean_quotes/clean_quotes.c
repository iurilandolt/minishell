/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:05:43 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 14:35:20 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"

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

void	clean_quotes(char **string, char flag)
{
	int		j;
	int		bar;
	t_qt	qt;
	char	*word;

	count_quotes(*string, &j, &qt, &bar);
	word = allocate_for_clean_word(j, qt.qt, qt.qts, bar);
	if (!word)
		return (perror(0));
	transfer_word(*string, word);
	if (flag)
		free(*string);
	*string = word;
}
