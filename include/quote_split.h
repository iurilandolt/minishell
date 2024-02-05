/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:37:11 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/05 15:38:37 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_qt
{
    int     qt;
    int     qts;
}   t_qt;

char	**quote_split(char const *s, char c);
char	**clean_quotes(char **table);
void    free_table(char **table);