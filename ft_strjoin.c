/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:49:36 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/11 10:55:43 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*strjoin;

	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	strjoin = malloc(len * sizeof(char));
	if (!strjoin)
		return (0);
	else
	{
		ft_strcpy(strjoin, s1);
		ft_strcpy(strjoin + ft_strlen(s1), s2);
		return (strjoin);
	}
}
