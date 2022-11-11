/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:43:21 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/10 16:43:21 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//TO DO
//Create a function that reads #buffer_amount until \n is found
//Store buffer in line
//Use get_next_line to trim characters after \name
//Return address of pointer to first char of the desired line

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize > 0)
	{
		i = 0;
		while ((src[i] != '\0') && (i < dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

int	ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (i);
}

char	*filter_line(char *buffer)
{
	int	i;
	char *line;

	i = 0;
	i = ft_strchr_index(buffer, '\n');
	line = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(line, buffer, i);
	return (*&line);
}

char	*read_btn(int fd, char *buffer)
{
	char	*btn;
	int		i;

	i = 0;
	btn = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!ft_strchr(buffer, '\n'))
	{
		read(fd, btn, BUFFER_SIZE);
		buffer = ft_strjoin(buffer, btn);
		i++;
	}
	return (buffer);
}

char	*second_line(char *buffer)
{
	int	i;
	char *second_line;

	i = 0;
	i = ft_strchr_index(buffer, '\n');
	second_line = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(second_line, buffer, i);
	return (second_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	buffer = read_btn(fd, buffer);
	line = filter_line(buffer);
	buffer = second_line(buffer);
	// printf("Buffer = %s.\n\n", buffer);
	return (line);
}
