/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiovann <egiovann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/07 23:29:04 by egiovann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl(char *buff, char *stash, char *line, fd);
{
	
	int	read_count;

	read_count = 1;
	while (read_count > 0 || ft_strchr(line, '\n') != -1)
	{
		if (ft_strchr(line, '\n') != -1)
			return (break_line(line, stash, ft_strchr(line, '\n')));
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		read_count = read(fd, buff, BUFFER_SIZE);
		if (read_count == 0)
			return (handle_end(buff, line));
		if (ft_strchr(buff, '\n') != -1)
		{
			line = ft_strjoin_and_free(line, buff);
			return (break_line(line, stash, ft_strchr(line, '\n')));
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

char	*cpy_cut_line(stash)
{
	char	*line;

	while (stash[i] != '\n' || stash[i] != '\0')
		line[i++] = stash[i++]
	line[i] = '\0';
	stash 
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
		// set the line from stash, and store the leftovers in static char
		// to do that, I have to call strchr
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
