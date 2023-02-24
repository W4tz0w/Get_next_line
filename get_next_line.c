/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/02/24 02:04:35 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_fill_stash(char *stash, int fd)
{
	int		bytes;
	char	*buff;

	bytes = 1;
	buff = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (gnl_strchr(stash, '\n') == -1 && gnl_strchr(stash, '\0') != 0 && bytes > 0)
	{
		// printf("pos is %d\n", gnl_strchr(stash, '\n'));
		bytes = read(fd, buff, BUFFER_SIZE);
		// printf("BUFF is %s\n", buff);
		if (bytes < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		// printf("FILLSTASH stash is %s\n", stash);
		stash = gnl_join_n_free(stash, buff);
	}
	free(buff);
	// printf("bytes is %d\n", bytes);
	return (stash);
}

char	*gnl_extract_line(char *stash, int pos)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	// printf("stash is : %s\n", stash);
	if (!stash)
	{
		// printf("stash doesn't exist");
		return (NULL);
	}
	line = gnl_calloc(pos + 2, sizeof(char));
	if (pos == -1)
	{
		while (stash[j] != '\0')
			line[i++] = stash[j++];
		stash[j++] = '\0';
	}
	if (pos > 0)
	{
		while (stash[j] && i < pos)
			line[i++] = stash[j++];
		if (stash[j] == '\n')
			line[i++] = '\n';
	}
	// stash[j] = '\0';
	line[i] = '\0';
	return (line);
}

char	*gnl_cpy_leftovers(char *stash, int pos)
{
	int		i;
	int		j;
	char	*temp;

	
	// printf("POS is : ''%d''\n", pos);
	i = 0;
	j = 1;
	if (pos == -1)
		return (NULL);
	// printf("stash =========CPYLEFTVRS is : ''%s''\n", stash);
	temp = gnl_calloc(gnl_strlen(stash + 1), sizeof(char));
	while (stash[j] != '\0')
		temp[i++] = stash[pos + j++];
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
	stash = gnl_fill_stash(stash, fd);
	if (stash[0] == '\0')
	{
		printf("yes this zorks\n");
		return (NULL);
	}
	pos = gnl_strchr(stash, '\n');
	line = gnl_extract_line(stash, pos);
	stash = gnl_cpy_leftovers(stash, pos);
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
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	fd4 = open("test4.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
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
