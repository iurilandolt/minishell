/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:53:05 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/06 17:33:40 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_analyzer(char *string)
{
	int	i;
	int	qt;
	int	qts;

	i = -1;
	qt = 0;
	qts = 0;
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
