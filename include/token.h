/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:18:09 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/11 13:27:20 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_type
{
	RED_IN,
	HERE_DOC,
	RED_OUT,
	RED_APP,
	STD,
	ARG,
	PRTS,
	PIPE,
	SAND,
	OR
}	t_type;

typedef struct s_token
{
	char			*value;
	int				type;
	char			**cmd;
}	t_token;

t_token		*tokenize(char *line);

t_token		*tok_create_array(char **split);
void		set_token_type(t_token *token);
t_token		*tok_free_array(t_token *tokens);

int			tokens_check(t_token *tokens);

#endif
