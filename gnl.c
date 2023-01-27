/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:43:27 by egiovann          #+#    #+#             */
/*   Updated: 2023/01/27 03:58:05 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_extract_line(char *stash, int p)
{
	int		i;
	int		j;
	char	*temp;
	char	*line;

	temp = NULL;
	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	line = gnl_calloc(p + 2, sizeof(char));
	while (stash && i < p)
		line[i++] = stash[j++];
	if (stash[j] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	i = 0;
	j = 0;
	while (stash)
		temp[i++] = stash[p + j++];
	temp[i] = '\0';
	free(stash);
	i = 0;
	j = 0;
	while (temp[j])
		stash[i++] = temp[j++];
	return (line);
}

char	*gnl_fill_stash(char *stash, int fd)
{
	int		bytes;
	char	*buff;

	bytes = 1;
	buff = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	printf("We successfully calloced, bytes value is : ''%d''\n", bytes);
	// while (gnl_strchr(stash, '\n') == -1 && bytes > 0)
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		printf("BUFF is : ''%s''\n", buff);
		if (bytes == -1)
		{
			free(buff);
			printf("EOF bytes == -1");
			return (NULL);
		}
		buff[bytes] = '\0';
		stash = gnl_join_n_free(stash, buff);
		printf("STASH is : ''%s''\n", stash);
		if (gnl_strchr(stash, '\n') == -1)
		{
			printf("================\n");
			printf("We reached end of fill stash 55\n");
			free(buff);
			return (stash);
		}
	}
	// printf("================\n");
	// printf("We reached end of fill stash 55\n");
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash;

	// printf("Fd is %d\n and BUFFer_SI~E is %d\n", fd, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	// printf("We reached here\n");
	stash = gnl_fill_stash(stash, fd);
	// create one if firsttimer // fill it with read until '\n' or EOF
	printf("Stash retrieved from gnl_fill_stash is :\n ''%s''\n", stash);
	if (!stash[0])
		return (NULL);
	line = gnl_extract_line(stash, gnl_strchr(stash, '\n'));
	printf("line extracted is %s\n", line);
	return (line);
	// return (ft_gnl(buff, stash, line, fd));
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
	// fd2 = open("/42_born_to_code/Stud'/Get_next_line/test2.txt", O_RDONLY);
	// fd3 = open("/42_born_to_code/Stud'/Get_next_line/test3.txt", O_RDONLY);
	// fd4 = open("/42_born_to_code/Stud'/Get_next_line/test4.txt", O_RDONLY);
	i = 1;
	while (i < 5)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		// line = get_next_line(fd2);
		// printf("line [%02d]: %s\n", i, line);
		// free(line);
		// line = get_next_line(fd3);
		// printf("line [%02d]: %s\n", i, line);
		// free(line);
		// line = get_next_line(fd4);
		// printf("line [%02d]: %s\n", i, line);
		// free(line);
		i++;
	}
	close(fd1);
	// close(fd2);
	// close(fd3);
	// close(fd4);
	return (0);
}