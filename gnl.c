/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:43:27 by egiovann          #+#    #+#             */
/*   Updated: 2023/01/29 03:36:07 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_extract_line(char *stash, int p)
{
	printf("inside GNL_EXTRACT_LINE\n");
	int		i;
	int		j;
	char	*temp;
	char	*line;

	temp[0] = '\0';
	i = 0;
	j = 0;
	if (stash == NULL)
		return (NULL);
	// line = gnl_calloc(p + 2, sizeof(char));
	// printf("LINE IS CALLOCED");
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
	printf("We successfully calloced BUFF, bytes value is : ''%d''\n", bytes);
	while (gnl_strchr(stash, '\n') == -1 && bytes > 0)
	// while (bytes > 0)
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
		// if (gnl_strchr(stash, '\n') == -1)
		// {
		// 	printf("================\n");
		// 	printf("We reached end of fill stash 55\n");
		// 	free(buff);
		// 	return (stash);
		// }
	}
	// printf("================\n");
	// printf("We reached end of fill stash 55\n");
	free(buff);
	return (stash);
}

char	*gnl_extract_two(char *stash, int pos)
{
	printf("inside GNL_EXTRACT_TWO\n");
	int		i;
	int		j;
	char	*temp;
	char	*line;

	temp = gnl_calloc(pos + 2, sizeof(char));
	printf("TEMP IS CALLOCED\n");
	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	line = gnl_calloc(pos + 2, sizeof(char));
	printf("LINE IS CALLOCED\n");
	while (stash[j] || i < pos)
		line[i++] = stash[j++];
	if (stash[j] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	printf("LINE extrct2 is : %s", line);
	// i = 0;
	// j = 1;
	// while (stash[j])
	// 	temp[i++] = stash[pos + j++];
	// // {
	// // 	temp[i] = stash[pos + i];
	// // 	i++;
	// // }
	// temp[i] = '\0';
	// printf("TEMP is %s\n", temp);
	// free((void *)stash);
	// stash = gnl_calloc(gnl_strlen(temp), sizeof(char));
	// i = 0;
	// j = 0;
	// while (temp[j])
	// 	stash[i++] = temp[j++];
	// printf("STASH IS (end extrct2) : %s\n", stash);
	// free(temp);
	return (line);
// 	return (NULL);
}

char		*gnl_cpy_leftovers(char *stash, int pos)
{
	printf("in cpy_leftovers stash is %s\n", stash);
	int		i;
	int		j;
	char	*temp;
	
	i = 0;
	j = 1;
	temp = gnl_calloc(gnl_strlen(stash + 1), sizeof(char));
	while (stash[j])
		temp[i++] = stash[pos + j++];
	temp[i] = '\0';
	printf("STASH IS (end CPY_LEFTOVERS) : %s\n", stash);
	return (temp);
}


char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash;
	int				pos;

	// printf("Fd is %d\n and BUFFer_SI~E is %d\n", fd, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	// printf("We reached here\n");
	stash = gnl_fill_stash(stash, fd);
	// create one if firsttimer // fill it with read until '\n' or EOF
	printf("================ gnl_fill_stash is :\n ''%s''\n", stash);
	if (stash[0] == '\0')
		return (NULL);
	// line = gnl_calloc((gnl_strchr(stash, '\n')) + 2, sizeof(char));
	// printf("LINE IS CALLOCED\n");
	pos = gnl_strchr(stash, '\n');
	line = gnl_extract_two(stash, pos);
	stash = gnl_cpy_leftovers(stash, pos);
	printf("STASH to be REUSED is %s\n", stash);
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