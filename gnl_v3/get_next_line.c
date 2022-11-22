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
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

char	*read_buffer(int fd, char *btn)
{
	char		*temp;
	int			bytes;

	temp = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!temp)
		return (NULL);
	bytes = 1;
	while ((!ft_strchr(btn, '\n') && bytes > 0))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		temp[bytes] = '\0';
		// if (bytes <= 0 && !btn)
		// {
		// 	free(btn);
		// 	free(temp);
		// 	return (NULL);
		// }
		// if (bytes == -1 && btn)
		// {
		// 	free(btn);
		// 	free(temp);
		// 	return (NULL);
		// }
		// else if (bytes == 0 && btn[0])
		// 	break ;
		if (bytes < 0)
		{
			free(temp);
			return (NULL);
		}
		btn = ft_strjoin(btn, temp);
	}
	free(temp);
	return (btn);
}

char	*filter_tnl(char *btn)
{
	int		nl_index;
	char	*current_line;

	if (!(ft_strchr(btn, '\n')))
		return (btn);
	nl_index = ft_strchr_index(btn, '\n');
	current_line = ft_substr(btn, 0, nl_index + 1);
	return (current_line);
}

char	*trim_tnl(char *btn)
{
	int		nl_index;
	int		size;
	char	*new_btn;

	// if (!(nl_index = ft_strchr_index(btn, '\n')))
	// 	return (NULL);
	if (!(ft_strchr(btn, '\n')))
		return (btn);
	nl_index = ft_strchr_index(btn, '\n');
	size = (ft_strlen(btn) - (nl_index + 1));
	//new_btn = ft_calloc(size, sizeof(char));
	new_btn = ft_substr_and_free(btn, nl_index + 1, size);
	//free(btn);
	return (new_btn);
}

char	*get_next_line(int fd)
{
	static char	*btn;
	char		*current_line;
	//static int	lines_read;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	// if ((btn = read_buffer(fd, btn)))
	// {
	btn = read_buffer(fd, btn);
	if (btn == NULL)
		return (NULL);
	current_line = filter_tnl(btn);
	btn = trim_tnl(btn);
	// }
	// else
	// {
	// 	free(btn);
	// 	return (NULL);
	// }
	// lines_read++;
	// printf("Line[%d]: %s\n", lines_read, current_line);
	return (current_line);
}

int	main()
{
	int fd;
	int	i;

	i = 0;
	fd = open("empty.txt", O_RDONLY);
	while (get_next_line(fd))
	{
		i++;
	}
	close(fd);
}
