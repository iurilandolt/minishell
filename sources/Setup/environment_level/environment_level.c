/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_level.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:30:08 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/29 18:30:44 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*environment_level(t_token *tokens, int ntasks)
{
	int	i;
	int	j;
	int	k;
	int	*environmentn;
	
	i = -1;
	j = 0;
	k = 0;
	environmentn = malloc(sizeof(int) * ntasks);
	while (tokens[++i].value)
	{
		if (tokens[i].type >= PIPE)
			j++;
		if (tokens[i].type == PRTS && tokens[i].value[0] == '(')
			k++;
		environment[j] = k;
		if (tokens[i].type == PRTS && tokens[i].value[0] == ')')
			k--;
	}
	return (environmentn);
}
