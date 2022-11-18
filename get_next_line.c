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
	if (s[i] == '\0')
		return (i - 1);
	return (i);
}

char	*read_buffer(int fd, char *current_line)
{
	char	temp[BUFFER_SIZE + 1];
	int		bytes;
	
	bytes = 1;
	while ((!ft_strchr(temp, '\n') && bytes > 0))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		temp[bytes] = '\0';
		if (bytes > 0)
			current_line = ft_strjoin(current_line, temp);
		if (!current_line && bytes <= 0)
			return (NULL);
	}
	return (current_line);
}

char	*get_next_line(int fd)
{
	static char	*btn;
	char		*current_line = NULL;
	int			nl_index;

	if (!(current_line = read_buffer(fd, current_line))) 
	{
		free(current_line);
		free(btn);
		return (NULL);
	}
	if (!btn) //On first iteration, when btn is empty, check for nl_index in current_line;
	{
		nl_index = ft_strchr_index(current_line, '\n');
	}
	else //Else if btn contains words after \n, append with current_line and find nl_index in concatenated current_line;
	{
		current_line = ft_strjoin(btn, current_line);
		nl_index = ft_strchr_index(current_line, '\n');
	}
	btn = ft_substr(current_line, nl_index + 1, ft_strlen(current_line + nl_index)); //Store everything after \n in btn;
	if (btn[0] == '\0')
		free(btn);
	current_line = ft_substr(current_line, 0, nl_index + 1); //Trim everything

	//printf("\nGNL output = %s", current_line);
	return (current_line);
}

// int	main()
// {
// 	int fd;
// 	//int	i;

// 	//i = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	while (get_next_line(fd))
// 	{
// 		// printf("\nget_next_line[%d] = %s", i, get_next_line(fd));
// 		// printf("\n------------------------------------\n");
// 		// i++;
// 	}
// 	close(fd);
// }
