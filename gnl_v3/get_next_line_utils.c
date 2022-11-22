/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:21:38 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/13 17:21:38 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	char				*ptr;
	size_t				i;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < (count * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

static size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*strjoin;
	//int		nl_index;

	// if ((nl_index = ft_strchr_index(s2, '\n')))
	// 	len = (ft_strlen(s1) + nl_index) + 1;
	// else
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	strjoin = malloc(len * sizeof(char));
	if (!strjoin)
		return (0);
	ft_strcpy(strjoin, s1);
	ft_strcpy(strjoin + ft_strlen(s1), s2);
	free(s1);
		return (strjoin);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (start > ft_strlen(s))
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (0);
	while (j < len && s[i] != '\0')
	{
		substr[j] = s[i + start];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

char	*ft_substr_and_free(char *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (start > ft_strlen(s))
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (0);
	while (j < len && s[i] != '\0')
	{
		substr[j] = s[i + start];
		i++;
		j++;
	}
	free(s);
	substr[j] = '\0';
	return (substr);
}
