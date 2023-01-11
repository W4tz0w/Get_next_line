/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiovann <egiovann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:43:27 by egiovann          #+#    #+#             */
/*   Updated: 2023/01/11 23:23:52 by egiovann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl(char *buff, char *stash, char *line, fd);
{
	if (ft_strchr(stash, '\n') != -1 || ft_strchr(stash, '\0') != -1)
		return (ft_copy_cut_line_from_stash(stash));
	else
	{
		bytes = read(buff, BUFFER_SIZE, fd);
		stash = ft_strjoin_and_free(stash, buff)
	}
		while (ft_strchr(stash, '\n') == -1 || ft_strchr(stash, '\0') == -1))
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
}
