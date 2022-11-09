
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *get_next_line(int fd)
{
	char 	*buffer;
	char	*buffer2;
	int		count;
	int		i;

	i = 0;
	count = 50;
	buffer = malloc(sizeof(char) * (count + 1));
	buffer2 = malloc(sizeof(char) * (count + 1));
	read(fd, buffer, count);
	buffer[count + 1] = '\0';
	while (buffer[i])
	{
		buffer2[i] = buffer[i];
		if (buffer[i] == '\n')
			break;
		i++;
	}
	printf("Backslash index at: %d\n", i);
	return (*&buffer2);
}

int	main(int argc, char **argv)
{
	char *buf;
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
			buf = malloc(sizeof(char) * get_next_line(fd));
			buf = get_next_line(fd);
			close (fd);
		}
	}
}