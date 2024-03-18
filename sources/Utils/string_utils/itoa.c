/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:31:34 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/11 10:42:31 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static int	int_chars(int nbr)
{
	int	chars;

	chars = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		chars++;
	}
	else if (nbr == 0)
		chars++;
	while (nbr > 0)
	{
		nbr /= 10;
		chars++;
	}
	return (chars);
}

char	*ft_itoa(int nbr)
{
	char	*new;
	int		size;

	if (nbr == -2147483648)
		return ("-2147483648\0");
	size = int_chars(nbr);
	if (size > 0)
		new = (char *)malloc(size * sizeof(char) + 1);
	else
		return (NULL);
	new[size] = '\0';
	if (nbr == 0)
		new[0] = '0';
	if (nbr < 0)
	{
		new[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		size--;
		new[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (new);
}

int	ft_atoi(const char *nptr)
{
	long int		n;
	int				sign;

	sign = 1;
	n = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr++ - '0');
		if (n > 2147483648)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
	}
	return (n * sign);
}
