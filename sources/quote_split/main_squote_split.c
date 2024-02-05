/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_squote_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:31:49 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/05 16:04:27 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_split.h"

void    free_table(char **table)
{
    int     i;

    i = 0;
    while (table[i])
        free(table[i++]);
    free(table);
}

int     main(int argc, char **argv)
{
    int     i;
    char    **table;

    i = 0;
    if (argc != 2)
        return (1);
    printf("%s\n", argv[1]);
    table = quote_split(argv[1], ' ');
    table = clean_quotes(table);
    while (table[i])
        printf("%s\n", table[i++]);
    free_table(table);
}