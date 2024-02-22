/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:44:27 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/22 18:45:03 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_readfrom(int **readfrom, int ntasks)
{
	int	i;
	
	i = -1;
	while (++i < ntasks)
		free(readfrom[i]);
	free(readfrom);
}
