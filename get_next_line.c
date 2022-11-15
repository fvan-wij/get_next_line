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
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			break ;
		i++;
	}
	return (i);
}

char	*read_buffer(int fd, char *btn)
{
	char	*temp;
	int		bytes;

	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	if (!temp)
		return (NULL);
	while ((!ft_strchr(temp, '\n') && bytes > 0))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes != 0)
			btn = ft_strjoin(btn, temp);
	}
	free(temp);
	return (btn);
}

char	*filter_tnl(char *btn)
{
	int		i;
	int		nl_index;
	char	*current_line;

	i = 0;
	nl_index = ft_strchr_index(btn, '\n');
	if (nl_index == 0)
		return (NULL);
	current_line = ft_calloc(nl_index, sizeof(char));
	if (!current_line)
		return (NULL);
	while (i <= nl_index)
	{
		current_line[i] = btn[i];
		i++;
	}
	return (current_line);
}

char	*trim_tnl(char *btn)
{
	int		i;
	int		nl_index;
	int		size;
	char	*new_btn;

	i = 0;
	nl_index = ft_strchr_index(btn, '\n');
	size = ft_strlen(btn) - nl_index;
	new_btn = ft_calloc(size, sizeof(char));
	if (!new_btn)
		return (NULL);
	while (btn[nl_index])
	{
		new_btn[i] = btn[nl_index + 1];
		i++;
		nl_index++;
	}
	free(btn);
	return (new_btn);
}

char	*get_next_line(int fd)
{
	static char *btn; //= "Buffer till newline"
	char		*current_line;

	if (!btn)
	{
		btn = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!btn)
			return (NULL);
	}
	//Read buffer up to BUFFER_SIZE till \n is found in buffer, concatenate every iteration and return buffer_till_newline (btn);
	btn = read_buffer(fd, btn);
	//Filter characters before the first occurrence of \n and store in current_line;
	current_line = filter_tnl(btn);
	//Store trimmed characters after first occurence of \n in btn;
	btn	= trim_tnl(btn);
	return (current_line);
}

int	main(int argc, char *argv[])
{
	int fd;
	int	i;
	int	n_of_lines;

	i = 0;
	n_of_lines = 0;
	fd = open(argv[1], O_RDONLY);
	if (argc == 3)
	{
		if (fd == -1)
		{
			write(1, "Failed to read file.\n", 22);
			exit (1);
		}
		else
		{
			n_of_lines = ft_atoi(argv[2]);
			while (i < n_of_lines)
			{
			printf("\nget_next_line[%d] = %s", i, get_next_line(fd));
			printf("\n------------------------------------\n");
			i++;
			}
		}
	}
	else
		write(1, "\nError: program needs 3 arguments ('executable | input | n of lines').\n\n", 72);
	close (fd);
}
