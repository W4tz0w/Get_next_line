/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiovann <egiovann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/12 21:14:21 by egiovann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl(char *buff, char *stash, char *line, fd);
{
	
	int	read_count;

	read_count = 1;
	// valeur de retour de "read"
	while (read_count > 0 || ft_strchr(line, '\n') != -1)
	// tant que j'ai qque chose a lire, OU si je trouve '\n'
	{
		if (ft_strchr(line, '\n') != -1)
			return (break_line(line, stash, ft_strchr(line, '\n')));
		// si je trouve '\n' >>> on renvoie la ligne / on copie les leftovers dans stash / free line / MAIS PAS FREE valeur retour
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		// reset buffer
		read_count = read(fd, buff, BUFFER_SIZE);
		// appel de read_fd
		// on set read_count, le but est de voir si y'a qque chose de lu, donc si on est pas deja a la fin du fd
		if (read_count == 0)
			return (handle_end(buff, line));
		// auquel cas, on retourne NULL (*** a verifier ***)
		// EH NON ! Car si rien n'a ete lu cet appel, il est fort probable qu'au precedent la stash eu ete remplie
		if (ft_strchr(buff, '\n') != -1)
		// apres un check pour '\n', puis un appel de read, puis un check pour '\0', on re-check '\n'
		{
			line = ft_strjoin_and_free(line, buff);
			// colle line+++buff. // free params. // (mais pas free variable de retour))
			return (break_line(line, stash, ft_strchr(line, '\n')));
			// on renvoie la ligne / on copie les leftovers dans stash / free line / MAIS PAS FREE valeur retour
		}
		else
			line = ft_strjoin_and_free(line, buff);
	}
	return (NULL);
}

char	*cpy_cut_line(char *src)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!res)
		return (NULL);
	while (src[i] != '\0')
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	src[0] = '\0';
	return (res);
}

char	*cpy_cut_line(char *stash)
{
	int		i;
	int		j;
	char	*line;
	char	*tmp;

	i = 0;
	j = 0;
	while (stash[i] != '\n' || stash[i] != '\0')
		line[i++] = stash[i++]
	line[i + 1] = stash[i + 1];
	while (stash[i] != '\0')
		tmp[j++] = stash[i++]
	stash[i] = '\0'
	free(stash)
	i = 0;
	while (tmp)
		stash[i++] = tmp[i++]
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buff;
	static char		stash[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = NULL;
	line = cpy_cut_line(stash);
		// calloc n set line from stash (obv if gnl was called at least one time before), and writes '\0' in stash[0]
	return (ft_gnl(buff, stash, line, fd));
		// return the line OR NULL
}

// {
// 	buffer = NULL;
// 	ssize_t = read(fd, buffer, BUFFER_SIZE);
// 	buffer = []
// 	STATIC stash += buffer
// 	if (end_of_file || param NULL || file_empty)
// 		return (NULL);
// 	return (ft_gnl = line);
// }

int	main()
{
	char	*stash;

	stash = "HelloDolly";	
	printf("%s", cpy_cut_line(stash));
	return (2);
}