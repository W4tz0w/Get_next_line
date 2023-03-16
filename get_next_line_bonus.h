/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:12:51 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/03/16 18:22:24 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
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