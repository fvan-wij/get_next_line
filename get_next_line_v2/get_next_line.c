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

int	ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == (char)c)
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

static char	*copy_buffer(char *buffer, char *line)
{
	int		len;
	char	*strjoin;
	int		nl_index;

	len = (ft_strlen(buffer) + ft_strlen(line)) + 1;
	strjoin = ft_calloc(len, sizeof(char));
	if ((nl_index = ft_strchr_index(buffer, '\n')))
	{
		len = (ft_strlen(line) + nl_index);
		strjoin = ft_calloc(len, sizeof(char));
		ft_strcpy(strjoin, line);
		ft_strlcpy(strjoin + ft_strlen(strjoin), buffer, nl_index + 1);
		return (free(line), strjoin);
	}
	if ((nl_index = ft_strchr_index(buffer, '\n')) && !ft_strchr_index(line, '\n'))
	{
			ft_strcpy(strjoin, line);
			ft_strlcpy(strjoin + ft_strlen(strjoin), buffer, nl_index + 2);
			return (free(line), strjoin);
	}
	else
	{
		ft_strcpy(strjoin, line);
		ft_strcpy(strjoin + ft_strlen(strjoin), buffer);
	}
	return (free(line), strjoin);
}

char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes;
	int			nl_index;

	bytes = 1;
	line = NULL;
	if ((buffer[0] != '\0') && (nl_index = ft_strchr_index(buffer, '\n')))
	{
		line = ft_substr(buffer, nl_index, ft_strlen(buffer + nl_index));
		buffer[0] = '\0';
	}
	while (!(ft_strchr(buffer, '\n')) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		if (bytes != 0)
			line = copy_buffer(buffer, line);
	}
	return (line);
}

int	main()
{
	int fd;
	int	i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 10)
	{
		printf("\nget_next_line[%d] = %s", i, get_next_line(fd));
		printf("\n------------------------------------\n");
		// if (get_next_line(fd) == NULL)
		// 	break ;
		i++;
	}
	close(fd);
}
