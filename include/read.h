/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:51:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/10 02:41:24 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ambient_variable_expansion(char **string, char **envp);
char	*string_expander(char *string);
char	*string_contracter(char *string);
int		check_analyzer(char *string);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		split_size(char **split);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

#endif
