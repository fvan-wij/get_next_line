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
			break ;
		i++;
	}
	// if (s[i] == '\0')
	// 	return (i - 1);
	return (i);
}

char	*read_buffer(int fd, char *btn)
{
	char	temp[BUFFER_SIZE + 1];
	int		bytes;

	if (fd == -1)
		return (NULL);
	//temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while ((!ft_strchr(temp, '\n') && bytes > 0))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		temp[bytes] = '\0';
		if (bytes == 0 && !btn)
			return (NULL);
		if (bytes != 0)
			btn = ft_strjoin(btn, temp);
	}
	return (btn);
}

char	*filter_tnl(char *btn)
{
	int		nl_index;
	char	*current_line;

	nl_index = ft_strchr_index(btn, '\n');
	current_line = ft_calloc(nl_index + 1, sizeof(char));
	current_line = ft_substr(btn, 0, nl_index + 1);
	return (current_line);
}

char	*trim_tnl(char *btn)
{
	int		nl_index;
	int		size;
	char	*new_btn;

	nl_index = ft_strchr_index(btn, '\n');
	size = ft_strlen(btn + nl_index - 1);
	if (size > 0)
	{
	new_btn = ft_calloc(size, sizeof(char));
	new_btn = ft_substr(btn, nl_index + 1, size);
	free(btn);
	}
	else
	{
		free(btn);
		return (NULL);
	}
	return (new_btn);
}

char	*get_next_line(int fd)
{
	static char	*btn;
	char		*current_line;

	if ((btn = read_buffer(fd, btn)))
	{
	current_line = filter_tnl(btn);
	btn = trim_tnl(btn);
	}
	else
	{
		free(btn);
		return (NULL);
	}
	printf("Current_line: %s\n", current_line);
	return (current_line);
}

// int	main()
// {
// 	int fd;
// 	//int	i;
// 	//int	n_of_lines;

// 	//i = 0;
// 	//n_of_lines = 0;
// 	fd = open("1char.txt", O_RDONLY);

// 	// if (argc == 3)
// 	// {
// 	// 	if (fd == -1)
// 	// 	{
// 	// 		write(1, "Failed to read file.\n", 22);
// 	// 		exit (1);
// 	// 	}
// 		// else
// 		// {
// 			// n_of_lines = ft_atoi(argv[2]);
// 			while (get_next_line(fd))
// 			{
// 				// printf("\nget_next_line[%d] = %s", i, get_next_line(fd));
// 				// printf("\n------------------------------------\n");
// 				// i++;
// 			}
// 	// 	}
// 	// }
// 	// else
// 	// 	write(1, "\nError: program needs 3 arguments ('executable | input | n of lines').\n\n", 72);
// 	// close (fd);
// 	close(fd);
// }
