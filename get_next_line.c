/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiovann <egiovann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/03/15 23:59:26 by egiovann         ###   ########.fr       */
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
		// printf("BUFF is : %s\n", buff);
		if (!buff)
			return (NULL);
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buff);
			return (NULL);
		}
		if (bytes == 0 && gnl_strlen(buff) == 0/* && gnl_strchr(stash, '\n') != -1*/)
		{
			free(buff);
			// printf("BYTES is : %d\n", bytes);
			// printf("GNL_STRLEN_STASH is : %d\n", gnl_strlen(stash));
			return (stash);
		}
		// buff[bytes] = '\0';
		stash = gnl_join_n_free(stash, buff);
		// printf("stash = '%s'\n", stash);
		free(buff);
	}
	return (stash);
}

/* Et pourquoi pas creer une ft DANS GNL, qui retiendrait en static la totalité du fd
(appel apres appel) pour tjr calloc une line qui ne puisse pas etre plus petite
que la precedente? (est-ce que la MOULINETTE serait OK?)

Le but etant d'eviter de laisser des traces d'une line qui a ete deja appelé

On pourrait sinon tenter de free cette line, mais alors comment la return? */

char	*gnl_extract_line(char *stash, int pos)
{
	int		i;
	int		j;
	char	*line;


	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	// printf("POS = %d", pos);
	if (pos == -1)
	{
		line = gnl_calloc((gnl_strlen(stash) + 1), sizeof(char));
		while (stash[j] && i < gnl_strlen(stash))
		{
			line[i] = stash[j];
			i++;
			j++;
		}
		line[i] = '\0';
	}
	if (pos >= 0)
	{
		line = gnl_calloc(pos + 2, sizeof(char));
		// printf("i = %d\n", i);
		while (stash[j] && i <= pos)
		{
			line[i] = stash[j];
			i++;
			j++;
		}
		// printf("et i = %d\n", i);
		// fflush(stdout);
		// if (stash[j] == '\n')
		// 	line[++i] = '\n';
		// printf("EXTRLINE is : %s\n", stash);
		
		line[i] = '\0';
	}
	return (line);
}

/*function that save what's after the '\n' char in the stash.
 * its arguments are :
 	* stash : the address of the static variable
	* pos : the pos of the first '\n' char in the string
 * it return a pointer to a string containing the leftovers of the stash
*/
char	*gnl_cpy_leftovers(char *stash, char *line, int pos)
{
	char	*tmp;
	int		i;

	if (pos < 0)
	{
		free(stash);
		return (NULL);
	}
	// printf("CPYLFTVERS stash is : %s\n", stash);
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
	// printf("CPYLFTVRS is : %s\n", tmp);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash = NULL;
	int				pos;

	// printf("MAIN STASH is : [%s]\n", stash);
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	stash = gnl_fill_stash(stash, fd);
	if (stash == NULL/* || gnl_strlen(stash) == 0*/)
	{
		return (NULL);
	}
	if (gnl_strlen(stash) == 0 || stash[0] == '\0')
	{
		// printf("stash is : [%s]\n", stash);
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

int	main() {
	int fd = open("test1.txt", O_RDONLY);
	char *line;

	for (int i = 0 ; i < 2 ; i ++) {
		line = get_next_line(fd);
		printf(">\t%s", line);
		free(line);
	}
	close(fd);
	fd = open("test1.txt", O_RDONLY);
	line = get_next_line(fd);
	printf(">\t%s", line);
	free(line);
}
