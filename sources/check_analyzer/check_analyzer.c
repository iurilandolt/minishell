/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:53:05 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/06 16:54:03 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_analyzer(char *string)
{
	int	i;
	int	qt;
	int	qts;

	i = -1;
	while (string[++i])
	{
		if (string[i] == '\'' && (i == 0 || string[i - 1] != '\\'))
			qt++;
		if (string[i] == '\"' && (i == 0 || string[i - 1] != '\\'))
			qts++;
		if (string[i] == '\\' && string[i + 1] == 0)
			return (1);
	}
	if (qt % 2 || qts % 2)
		return (1);
	return (0);
}
