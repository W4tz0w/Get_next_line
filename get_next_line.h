/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiovann <egiovann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:45:03 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/12 23:18:19 by egiovann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 11
# endif

# include <stdio.h>
# include <stddef.h>
# include <unistd.h>

char	*ft_gnl(char *buff, char *stash, fd);
int		ft_strlen(const char *str);
int		ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);


#endif