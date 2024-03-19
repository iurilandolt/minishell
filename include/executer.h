/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:35:56 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/19 12:01:48 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "token.h"

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
	char		*line;
	int			ntasks;
	int			**pipes;
	t_token		*tokens;
	char		***commands;
	int			**readfrom;
	t_token		**writeto;
	t_operator	*operators;
	char		**menvp;
	int			*p_ids;
	int			status;

}	t_session;

void		print_session(t_session *all);

void		close_opened_fds(t_session *session, int writefd);
void		perform_tasks(t_session *session);
int			*list_process_ids(int ntasks);
void		perform_redirects(t_session *session, int taskn, int writefd);
void		ambient_variable_expansion(t_session *session,
				char **string, char flag);
void		organize_after_expansion(char ***command);
int			**obtain_read_documents(t_token *tokens,
				int **pipefd, t_session *session);
char		***obtain_commands(t_token *tokens, int ntasks);
t_operator	*operator_rules(t_token *tokens);
int			**create_pipes(t_operator *operators);

int			check_builtin(t_session *session, int taskn);
void		builtin_task(t_session *session, int taskn, int builtn);
int			open_builtin_taskfiles(t_session *session, int taskn);
char		*validate_bin_path(char **envp, char *cmd);
void		link_cmd_codes(t_session *session, int taskn, char *cmd);

void		free_session(t_session *session);
void		free_args(char **table);

int			open_taskfiles(t_session *session, int taskn);
t_token		**obtain_write_documents(t_token *tokens, int ntasks);

#endif
