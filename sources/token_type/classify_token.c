/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:42:13 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/11 00:56:06 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/token.h"
#include "../../include/read.h"

void	set_token_type(t_token *token)
{
	if (!token->value)
		return ;
	else if (ft_strncmp(token->value, ">>", 2) == 0)
		token->type = RED_APP;
	else if (ft_strncmp(token->value, "<<", 2) == 0)
		token->type = HERE_DOC;
	else if (ft_strncmp(token->value, ">", 1) == 0)
		token->type = RED_OUT;
	else if (ft_strncmp(token->value, "<", 1) == 0)
		token->type = RED_IN;
	else if (ft_strncmp(token->value, "|", 1) == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->value, "&", 1) == 0)
		token->type = SAND;
	else
		token->type = STD;
}

void	tok_expand_cmd(t_token *head)
{
	t_token	*tmp;
	int		cmd;

	cmd = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == STD && cmd == 0)
			cmd = 1;
		else if (tmp->type == STD && cmd == 1)
			tmp->type = ARG;
		else if (tmp->type != STD)
			cmd = 0;
		tmp = tmp->next;
	}

}

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;

	if (!str1 || !str2)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	while (*(str1 + ++i))
		*(dest + i) = *(str1 + i);
	while (str2[j])
		*(dest + i++) = *(str2 + j++);
	*(dest + i) = '\0';
	free((char *)str1);
	return (dest);
}

void	tok_contract_cmd(t_token *head)
{
	t_token	*tmp;
	t_token	*dest;
	t_token	*target;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == STD && tmp->next && tmp->next->type == ARG)
		{
			dest = tmp;
			tmp = tmp->next;
			while (tmp && tmp->type == ARG)
			{
				target = tmp;
				dest->value = ft_strjoin(dest->value, target->value);
				tmp = target->next;
				tok_remove(head, target);
			}
		}
		else
			tmp = tmp->next;
	}
	(void)dest;
}
