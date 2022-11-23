/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:43:21 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/23 17:49:18 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != (char)c)
		i++;
	return (i);
}

char	*read_buffer(int fd, char *btnl)
{
	char		*temp;
	int			bytes;

	temp = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!temp)
		return (NULL);
	bytes = 1;
	while ((!ft_strchr(btnl, '\n') && bytes > 0))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(temp), free(btnl), NULL);
		temp[bytes] = '\0';
		btnl = ft_strjoin_and_free(btnl, temp);
	}
	free(temp);
	return (btnl);
}

char	*filter_tnl(char *btnl)
{
	int		nl_index;
	char	*current_line;

	if (btnl[0] == '\0')
		return (NULL);
	nl_index = ft_strchr_index(btnl, '\n');
	current_line = ft_substr(btnl, 0, nl_index + 1);
	if (!current_line)
		free(btnl);
	return (current_line);
}

char	*trim_tnl(char *btnl)
{
	int		nl_index;
	char	*new_btnl;

	if (!(ft_strchr(btnl, '\n')))
		return (free(btnl), NULL);
	nl_index = ft_strchr_index(btnl, '\n');
	new_btnl = ft_substr(btnl, nl_index + 1, ft_strlen(btnl) + nl_index + 1);
	free(btnl);
	return (new_btnl);
}

char	*get_next_line(int fd)
{
	static char	*btnl[OPEN_MAX];
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	btnl[fd] = read_buffer(fd, btnl[fd]);
	if (btnl[fd] == NULL)
		return (NULL);
	current_line = filter_tnl(btnl[fd]);
	btnl[fd] = trim_tnl(btnl[fd]);
	return (current_line);
}

// int	main()
// {
// 	int 	fd_a;
// 	int		fd_b;
// 	int		i;
// 	int		j;
// 	char	*line_a;
// 	char	*line_b;

// 	i = 0;
// 	fd_a = open("read_error.txt", O_RDONLY);
// 	fd_b = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line_a = get_next_line(fd_a);
// 		printf("Line[%d]: %s\n", i, line_a);
// 		line_b = get_next_line(fd_b);
// 		printf("Line[%d]: %s\n", j, line_b);
// 		if (line_a == NULL && line_b == NULL)
// 			break ;
// 		i++;
// 		j++;
// 	}
// 	close(fd_a);
// 	close(fd_b);
// }
