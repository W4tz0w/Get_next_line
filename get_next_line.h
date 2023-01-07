/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:45:03 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/06 02:34:22 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 11
# endif

# include <stdio.h>
# include <stddef.h>

int ft_strlen(const char *s);
int	ft_strchr(char *s, int c);
void *ft_calloc(size_t count, size_t size);
char *get_next_line(int fd);


#endif