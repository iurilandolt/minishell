/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:35:56 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/20 15:56:06 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
#define EXECUTER_H

#include "token.h"

typedef struct s_operator
{
    int     flag;
    t_token *token;
}   t_operator;

typedef struct s_all
{
	int	(*pipefd)[2];
	t_token *tokens;
	t_cmdblock  *cmdblocks;
	t_operator  *operators;
}   t_all;

t_operator	*operator_rules(t_token *tokens);
int	(*create_pipes(t_operator *operators))[2];

#endif
