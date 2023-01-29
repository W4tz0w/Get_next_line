/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:45:03 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/29 03:16:45 by daddy_cool       ###   ########.fr       */
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
# include <stdlib.h>
# include <fcntl.h>

// char		*ft_gnl(char *buff, char *stash, int fd);
int			gnl_strlen(const char *s);
int			gnl_strchr(const char *s, char c);
char		*gnl_calloc(int count, int size);
static char	*gnl_join(char const *stash, char const *buff, char *str);
char		*gnl_join_n_free(char const *stash, char const *buff);
char		*gnl_fill_stash(char *stash, int fd);
char		*gnl_extract_line(char *stash, int p);
char		*gnl_extract_two(char *stash, int pos);
char		*gnl_cpy_leftovers(char *stash, int pos);
char		*get_next_line(int fd);


#endif