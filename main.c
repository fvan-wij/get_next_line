/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:44:06 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/11 17:15:15 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
	
		if (fd == -1)
		{
			write(1, "Failed to read file.\n", 22);
			exit (1);
		}
		else
		{
			//printf("%s", get_next_line(fd));
			get_next_line(fd);
			close (fd);
		}
	}
	else
	{
		write(1, "Program only accepts a.out + dictionary file.\n", 47);
		return (-1);
	}
}
