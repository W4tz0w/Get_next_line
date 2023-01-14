/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiovann <egiovann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:43:27 by egiovann          #+#    #+#             */
/*   Updated: 2023/01/14 20:42:51 by egiovann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_extract_line(char *stash, int p)
{
	int		i;
	int		length;
	char	*temp;
	char	*line

	i = 0;
	line = gnl_calloc(p + 2, sizeof(char));
	while (i <= p)
		line[i++] = stash[i++];
	line[i] = '\0';
	i = 0;
	t_length = gnl_strlen(stash);
	while (stash)
		temp[i++] = stash[p + 1 + i++];
	temp[i] = '\0';
	free(stash);
	while (temp)
		stash[i++] = temp[i++]
	return (line);
}

char	*ft_gnl(char *buff, char *stash, char *line, fd);
{
	while (gnl_strchr(stash, '\n') != -1)
	
		if (gnl_strchr(stash, '\n') != -1)
			return (gnl_extract_line(stash, gnl_strchr(stash, '\n')));
		buff = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
		bytes = read(buff, BUFFER_SIZE, fd);
		stash = gnl_join_n_free(stash, buff)

		
		
		while (gnl_strchr(stash, '\n') == -1 || gnl_strchr(stash, '\0') == -1))
		{
			
		}


}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buff;
	static char		stash[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	ft_gnl(buff, stash, line)
}
