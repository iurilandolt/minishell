/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:18:09 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/25 15:15:58 by rlandolt         ###   ########.fr       */
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
	struct s_token	*next;
}	t_token;

typedef struct s_cmdblock
{
	char	**cmd;
	t_token	*redin;
	t_token	*redout;
}	t_cmdblock;

t_token		*tokenize(char *line, char **envp);

t_token		*tok_create_array(char **split);
void		set_token_type(t_token *token);
t_token		*tok_free_array(t_token *tokens);



t_cmdblock	*create_cmdblocks(t_token *tokens);
void		print_cmdblocks(t_cmdblock *cmdblocks);
void		free_cmdblocks(t_cmdblock *cmdblocks);

int			tokens_check(t_token *tokens);

#endif
