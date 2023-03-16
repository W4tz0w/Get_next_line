/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/03/16 17:47:32 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char		*stash = NULL;
	int				pos;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{	
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = gnl_fill_stash(stash, fd);
	if (stash == NULL)
		return (NULL);
	if (gnl_strlen(stash) == 0 || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	pos = gnl_strchr(stash, '\n');
	line = gnl_extract_line(stash, pos);
	stash = gnl_cpy_leftovers(stash, line, pos);
	return (line);
}

// int	main(void)
// {
// //	printf("\033(0");
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
// 		// fflush(stdout);
// 		printf("line [%02d]: %s\n", i, line);
// 		free(line);
// 		// line = get_next_line(fd2);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		// line = get_next_line(fd3);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		// line = get_next_line(fd4);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	system("leaks a.out");
// //	printf("\033(1");
// 	return (0);
// }
