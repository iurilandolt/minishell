/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:35:56 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/24 14:44:49 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
#define EXECUTER_H

#include "token.h"
#include <sys/stat.h>

typedef struct s_operator
{
    int     flag;
    t_token *token;
}   t_operator;

typedef struct s_path_tools
{
	int		i;
	char	*path;
	char	*program;
	char	**paths;
}	t_path_tools;

typedef struct s_session
{
	int			ntasks;
	int			(*pipes)[2];
	t_token 	*tokens;
	char		***commands;
	int			**readfrom;
	t_token		**writeto;
	t_operator	*operators;

}   t_session;

t_token		**obtain_write_documents(t_token *tokens, int ntasks);
void		print_session(t_session *all);
char		*check_bin_path(char **envp, char *cmd);
int			**obtain_read_documents(t_token *tokens, int (*pipefd)[2], int ntasks);
char		***obtain_commands(char **envp, t_token *tokens, int ntasks);
t_operator	*operator_rules(t_token *tokens);
int			(*create_pipes(t_operator *operators))[2];

char	*validate_bin_path(char **envp, char *cmd);
int link_command(char *cmd);

#endif
