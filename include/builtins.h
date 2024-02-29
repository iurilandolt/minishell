/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:23:14 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/29 17:41:44 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/stat.h>
# include <dirent.h>

// CD & PWD
typedef struct s_cd
{
	char	*home;
	char	*pwd;
	char	*oldpwd;
}	t_cd;

void	setup_cd(t_cd *cd, char **envp);
void	change_dir(t_cd *cd, char *path);
void	free_cd(t_cd *cd);

char	**setup_menvp(char **envp);
void	menvp(char **menvp);

void	mpwd(void);

#endif
