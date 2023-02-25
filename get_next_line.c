/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/02/25 23:09:31 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*DEBUG=========================================================================*/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
/*DEBUG=========================================================================*/
char	*gnl_fill_stash(char *stash, int fd)
{
	// dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	// printf("stash is \033[1m|%s|\033[0m\n", stash);
	int		bytes;
	char	*buff;

	bytes = 1;
	while (gnl_strchr(stash, '\n') == -1 && bytes > 0)
	{
		buff = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		bytes = read(fd, buff, BUFFER_SIZE);
		// dprintf(2, "read %d char : |\033[1m%s\033[0m|\n", bytes, buff);//DEBUG
		if (bytes < 0)
		{
			// dprintf(2, "exiting %s (%s:%d) : SECU 1\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
			free(buff);
			return (NULL);
		}
		if (bytes == 0 && gnl_strlen(buff) == 0)
		{
			// dprintf(2, "exiting %s (%s:%d) : SECU 2\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
			free(buff);
			return (stash);
		}
		buff[bytes] = '\0';
		// dprintf(2, "buff is : |\033[1m%s\033[0m|\n", buff);//DEBUG
		stash = gnl_join_n_free(stash, buff);
		// dprintf(2, "joined it all : |\033[1m%s\033[0m|\n", stash);//DEBUG
		free(buff);
	// printf("end of FILLSTASH : %s\n", stash);
	}
	return (stash);
}

char	*gnl_extract_line(char *stash, int pos)
{
	int		i;
	int		j;
	char	*line;

	i = -1;
	j = -1;
	if (!stash)
		return (NULL);
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
	return (line);
}

/*function that save what's after the '\n' char in the stash.
 * its arguments are :
 	* stash : the address of the static variable
	* pos : the pos of the first '\n' char in the string
 * it return a pointer to a string containing the leftovers of the stash
*/
char	*gnl_cpy_leftovers(char *stash, int pos)
{
	//dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	//dprintf(2, "stash is \033[1m|%s|\033[0m; pos = %d\n", stash, pos);//DEBUG
	char	*tmp;
	int		i;

	if (pos < 0) {
		//dprintf(2, "SECU 1 : pos = %d\n", pos);//DEBUG
		return NULL;}
	//alocate temporary string (size = BUFFER_SIZE)
	tmp = gnl_calloc(BUFFER_SIZE, sizeof (char));
	if (!tmp) {
		//dprintf(2, "SECU 2\n");//DEBUG
		return (NULL);}
	//copy in temp the content of stash + pos;
	i = 0;
	pos ++;
	while ((stash + pos)[i] != '\0')
	{
		tmp[i] = (stash + pos)[i];
		i ++;
	}
	//dprintf(2, "tmp is %s\n", tmp);//DEBUG
	return tmp;
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash;
	int				pos;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	stash = gnl_fill_stash(stash, fd);
	if (stash == NULL || stash[0] == '\0')
	{
		free(stash);
		return (NULL);
	}
	pos = gnl_strchr(stash, '\n');
	line = gnl_extract_line(stash, pos);
	stash = gnl_cpy_leftovers(stash, pos);
	//dprintf(2, "stash is %s\n", stash);//DEBUG
	return (line);
}

int	main(void)
{
//	printf("\033(0");
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
//	system("leaks a.out");
//	printf("\033(1");
	return (0);
}
