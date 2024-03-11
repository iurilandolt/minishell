/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:24:00 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/11 12:28:48 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

static int	exp_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

static int	exp_is_alphanum(char c)
{
	if (exp_is_alpha(c) || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static int	is_validchar(char c)
{
	char	*valid = "*.:/_-=@+!"; // %&?{}[]()~^$#
	int		i;

	i = 0;
	while (valid[i])
	{
		if (c == valid[i])
			return (1);
		i++;
	}
	if (exp_is_alphanum(c))
		return (1);
	return (0);
}

int is_valid_env_format(const char *str)
{
	int	i;

	if (!ft_strncmp(str, "_=", 2) || !ft_strncmp(str, "_+=", 3)
		|| (str[0] == '_' && str[1] == '\0')
		|| (str[0] == '_' && str[1] == '='))
		return (0);
	if (!str || *str == '\0' || !exp_is_alpha(str[0]))
		return 0;
	i = 0;
	while(str[i] && exp_is_alphanum(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	if(str[i] == '+')
		i++;
	if(str[i] != '=')
		return (0);
	i++;
	if (!is_validchar(str[i]) && str[i] != '\0')
		return (0);
	while (is_validchar(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
