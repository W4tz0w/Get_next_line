/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:45:03 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/03/01 02:05:21 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 111
# endif

# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int			gnl_strlen(const char *s);
int			gnl_strchr(const char *s, char c);
char		*gnl_calloc(int count, int size);
char		*gnl_join_n_free(char *stash, char *buff);
char		*gnl_fill_stash(char *stash, int fd);
char		*gnl_extract_line(char *stash, int pos);
char		*gnl_cpy_leftovers(char *stash, char *line, int pos);
char		*get_next_line(int fd);

#endif