/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:18:09 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/10 01:46:13 by rlandolt         ###   ########.fr       */
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
	PIPE,
	SAND,
	STD,
	ARG
}	e_type;

typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

t_token *tok_create_array(char **split);
void	tok_free_array(t_token *tokens, int i);

#endif
