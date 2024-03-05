/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:35:56 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/05 12:07:35 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "token.h"
# include "builtins.h"
# include <sys/wait.h>

typedef struct s_operator
{
	int		flag;
	t_token	*token;
}	t_operator;

typedef struct s_path_tools
{
	char	*path;
	char	*program;
	char	**paths;
}	t_path_tools;

typedef struct s_session
{
	int			ntasks;
	int			(*pipes)[2];
	t_token		*tokens;
	char		***commands;
	int			**readfrom;
	t_token		**writeto;
	t_operator	*operators;
	int			*envlvl;
	char		***menvp;
	t_cd		cd;
}	t_session;

void		print_session(t_session *all);

void		close_opened_fds(t_session *session, int writefd);
void		perform_tasks(t_session *session);
int			prepare_writefds(t_session *session, int taskn);
void		perform_redirects(t_session *session, int taskn, int writefd);

int			**obtain_read_documents(t_token *tokens, int (*pipefd)[2], int ntasks);
char		***obtain_commands(t_token *tokens, int ntasks);
t_operator	*operator_rules(t_token *tokens);
int			(*create_pipes(t_operator *operators))[2];

int			check_builtin(t_session *session, int taskn);
void		exec_builtin(t_session *session, int taskn, int builtin);
char		*validate_bin_path(char **envp, char *cmd);
void		link_cmd_codes(char *cmd);

void		free_session_commands(t_session *session);
int			free_session(t_session *session, char flag);

int	open_taskfiles(t_session *session, char **menvp, int taskn);
t_token	**obtain_write_documents(t_token *tokens, int ntasks);

int	*environment_levels(t_session *session, t_token *tokens, char **menvp);
char	**correct_environment(t_session *session, int taskn);

#endif
