/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:37:11 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/06 10:54:17 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_SPLIT_H
# define QUOTE_SPLIT_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_qt
{
	int	qt;
	int	qts;
}	t_qt;

char	**quote_split(char const *s, char c);
char	**clean_quotes(char **table);
void	free_table(char **table);

#endif
