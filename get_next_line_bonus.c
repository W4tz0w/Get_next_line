/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:07:43 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/03/16 18:21:24 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_fill_stash(char *stash, int fd)
{
	int		bytes;
	char	*buff;

	bytes = 1;
	while (gnl_strchr(stash, '\n') == -1 && bytes > 0)
	{
		buff = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buff);
			return (NULL);
		}
		if (bytes == 0 && gnl_strlen(buff) == 0)
		{
			free(buff);
			return (stash);
		}
		stash = gnl_join_n_free(stash, buff);
		free(buff);
	}
	return (stash);
}

char	*gnl_extract_line(char *stash, int pos)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	if (pos == -1)
	{
		line = gnl_calloc((gnl_strlen(stash) + 1), sizeof(char));
		while (stash[j] && i < gnl_strlen(stash))
			line[i++] = stash[j++];
	}
	if (pos >= 0)
	{
		line = gnl_calloc(pos + 2, sizeof(char));
		while (stash[j] && i <= pos)
			line[i++] = stash[j++];
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_cpy_leftovers(char *stash, char *line, int pos)
{
	char	*tmp;
	int		i;

	if (pos < 0)
	{
		free(stash);
		return (NULL);
	}
	tmp = gnl_calloc(gnl_strlen(stash) - gnl_strlen(line) + 1, sizeof (char));
	if (!tmp)
		return (NULL);
	i = 0;
	++ pos;
	while (stash[pos + i] != '\0')
	{
		tmp[i] = (stash[pos + i]);
		++ i;
	}
	tmp[i] = '\0';
	free(stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash[4096];
	int				pos;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{	
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = gnl_fill_stash(stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	if (gnl_strlen(stash[fd]) == 0 || stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	pos = gnl_strchr(stash[fd], '\n');
	line = gnl_extract_line(stash[fd], pos);
	stash[fd] = gnl_cpy_leftovers(stash[fd], line, pos);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		fd4;

// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	fd3 = open("test3.txt", O_RDONLY);
// 	fd4 = open("test4.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 11)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s\n", i, line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("line [%02d]: %s\n", i, line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("line [%02d]: %s\n", i, line);
// 		free(line);
// 		line = get_next_line(fd4);
// 		printf("line [%02d]: %s\n", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	system("leaks a.out");
// 	return (0);
// }
