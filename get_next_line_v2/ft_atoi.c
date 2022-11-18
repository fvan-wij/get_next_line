/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:18:26 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/12 16:18:26 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	skip_whitespace(int i, char *int_str)
{
	while (int_str[i] == ' ' || int_str[i] == '\t'
		|| int_str[i] == '\r' || int_str[i] == '\n'
		|| int_str[i] == '\v' || int_str[i] == '\f')
	i++;
	return (i);
}

static int	convert_atoi(char *int_str, int i)
{
	int	atoi;

	atoi = 0;
	while ((int_str[i] >= 48 && int_str[i] <= 57) && int_str[i] != '\0')
	{
		atoi = atoi * 10 + (int_str[i] - '0');
		i++;
	}
	return (atoi);
}

int	ft_atoi(const char *nptr)
{
	char	*int_str;
	int		atoi;
	int		i;
	int		j;
	int		neg_check;

	int_str = (char *) nptr;
	atoi = 0;
	i = 0;
	j = 0;
	neg_check = 1;
	i = skip_whitespace(i, int_str);
	if (int_str[i] == '-')
		neg_check = -neg_check;
	while (int_str[i] == '-' || int_str[i] == '+')
	{
		i++;
		j++;
		if (j > 1)
			return (0);
	}
	atoi = convert_atoi(int_str, i);
	return (atoi * neg_check);
}
