/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/29 04:02:41 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_fill_stash(char *stash, int fd)
{
	int		bytes;
	char	*buff;

	bytes = 1;
	buff = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (gnl_strchr(stash, '\n') == -1 && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		stash = gnl_join_n_free(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*gnl_extract_line(char *stash, int pos)
{
	int		i;
	int		j;
	char	*temp;
	char	*line;

	temp = gnl_calloc(pos + 2, sizeof(char));
	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	line = gnl_calloc(pos + 2, sizeof(char));
	// YOOOO PROBLEME ICI (dans le while || ou && )
	if (pos == -1)
	{
		while (stash[j])
			line[i++] = stash[j++];
	}
	if (pos > 0)
	{
		while (stash[j] && i < pos)
			line[i++] = stash[j++];
		if (stash[j] == '\n')
			line[i++] = '\n';
	}
	line[i] = '\0';
	return (line);
}

char		*gnl_cpy_leftovers(char *stash, int pos)
{
	int		i;
	int		j;
	char	*temp;
	
	i = 0;
	j = 1;
	temp = gnl_calloc(gnl_strlen(stash + 1), sizeof(char));
	while (stash[j])
		temp[i++] = stash[pos + j++];
	temp[i] = '\0';
	return (temp);
}


char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash;
	int				pos;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stash = gnl_fill_stash(stash, fd);
	if (stash[0] == '\0')
		return (NULL);
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
	while (i < 5)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		line = get_next_line(fd4);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
}