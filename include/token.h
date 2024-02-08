/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:18:09 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/08 14:43:44 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum s_type
{
	RED_IN,
	RED_OUT,
	RED_APP,
	HERE_DOC,
	OPERATOR,
	EVAR,
	UNHANDLED,
}	e_type;

typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

t_token *gen_tokens(char **split);
void	free_tokens(t_token *tokens, int i);

#endif
