/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:44:29 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/07 17:00:56 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer;
	static char		stash[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = NULL;
	line = cpy_src(stash);
	return (ft_get_next_line(line, buffer, stash, fd));
}

{
	buffer = NULL;
	ssize_t = read(fd, buffer, BUFFER_SIZE);
	buffer = []
	STATIC stash += buffer
	if (end_of_file || param NULL || file_empty)
		return (NULL);
	return (ft_gnl = line);
}
