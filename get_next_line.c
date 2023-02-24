/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/02/24 21:57:17 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_fill_stash(char *stash, int fd)
{
	int		bytes;
	char	*buff;

	bytes = 1;
	printf("FILLSTASH stash is %s\n", stash);
	while (gnl_strchr(stash, '\n') == -1 && bytes > 0)
	{
		buff = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
		// printf("pos is %d\n", gnl_strchr(stash, '\n'));
		bytes = read(fd, buff, BUFFER_SIZE);
		// printf("BUFF is %s, bytes is %d\n", buff, bytes);
		if (bytes < 0)
		{
			free(buff);
			return (NULL);
		}
		if (bytes == 0 && gnl_strlen(buff) == 0)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		stash = gnl_join_n_free(stash, buff);
		free(buff);
	}
	// printf("bytes is %d\n", bytes);
	return (stash);
}

char	*gnl_extract_line(char *stash, int pos)
{
	int		i;
	int		j;
	char	*line;

	i = -1;
	j = -1;
	// printf("stash is : %s\n", stash);
	// printf("pos is %d\n", pos);
	if (!stash)
	{
		printf("stash doesn't exist");
		return (NULL);
	}
	line = gnl_calloc(pos + 2, sizeof(char));
	if (pos == -1)
	{
		while (stash[++j] != '\0')
			line[++i] = stash[j];
		// stash[j++] = '\0';
	}
	if (pos > 0)
	{
		while (stash[++j] && i < pos)
			line[++i] = stash[j];
		if (stash[j] == '\n')
			line[++i] = '\n';
	}
	line[++i] = '\0';
	// stash[j] = '\0';
	// printf("Line is %s\n", line);
	return (line);
}

char	*gnl_cpy_leftovers(char *stash, int pos)
{
	int		i;
	int		j;
	char	*temp;
	
	// printf("POS is : ''%d''\n", pos);
	i = -1;
	j = -1;
	if (pos == -1)
		return (NULL);
	printf("stash CPYLEFTVRS is : ''%s'', pos is %d, len is %d \n", stash, pos, gnl_strlen(stash));
	temp = gnl_calloc(gnl_strlen(stash) - pos, sizeof(char));
	while (stash[++j] != '\0')
	{
		temp[++i] = stash[pos + 1 + j];
	}
	temp[i] = '\0';
	// printf("LEFTOVERS are : ''%s''\n", temp);
	// printf("stash BEFORE free is : ''%s''\n", stash);
	free(stash);
	// printf("stash AFTER free is : '%s'\n", stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash;
	int				pos;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	printf("Stash in Main is %s\n", stash);
	stash = gnl_fill_stash(stash, fd);
	if (stash[0] == '\0')
	{
		printf("yes this zorks\n");
		free(stash);
		return (NULL);
	}
	printf("Stash read \"%s\"\n", stash);
	pos = gnl_strchr(stash, '\n');
	printf("Pos detected is %d\n", pos);
	line = gnl_extract_line(stash, pos);
	printf("Line captured to return is %s\n", line);
	stash = gnl_cpy_leftovers(stash, pos);
	printf("Stash is now updated to %s\n", stash);
	return (line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;

	printf("%d\n", gnl_strlen("Hello"));
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	fd4 = open("test4.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		fflush(stdout);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		// line = get_next_line(fd2);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// line = get_next_line(fd3);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// line = get_next_line(fd4);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	system("leaks a.out");
	return (0);
}
