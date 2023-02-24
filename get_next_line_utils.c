/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 03:42:24 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/02/24 21:57:41 by daddy_cool       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

char	*gnl_calloc(int count, int size)
{
	char	*ptr;
	int		i;
	
	// printf("inside CALLOC, size is ===== %d, count is %d\n", size, count);
	ptr = (char *)malloc(count * size);
	// printf("CALLOC went OK\n");
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ptr[i] = 0;
		++i;
	}
	return (ptr);
}

int	gnl_strchr(const char *s, char c)
{
	int		i;

	i = 0;
	if (s == NULL)
	{
		return (-1);
	}
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (i);
		}
		++i;
	}
	if (s[i] == c)
	{
		return (i);
	}
	return (-1);
}

char	*gnl_join(char *stash, char *buff, char *str)
{
	int		i;
	int		buff_len;
	int		stash_len;

	i = 0;
	buff_len = gnl_strlen(buff);
	stash_len = gnl_strlen(stash);
	while (stash && i < stash_len)
	{
		str[i] = stash[i];
		++i;
	}
	i = 0;
	while (buff && i < buff_len)
	{
		str[stash_len + i] = buff[i];
		++i;
	}
	str[stash_len + i] = '\0';
	// printf("STASH + BUFF\n");
	return (str);
}

char	*gnl_join_n_free(char *stash, char *buff)
{
	char	*str;
	int		stash_buff_len_1;

	// printf("buff size is %d\n", gnl_strlen(buff));
	// printf("stash size is %d\n", gnl_strlen(stash));
	stash_buff_len_1 = gnl_strlen(stash) + gnl_strlen(buff) + 1;
	// printf("stash_buff_len_1 = %d\n", stash_buff_len_1);
	// if (stash_buff_len_1 > 1)
	str = (char *)gnl_calloc(stash_buff_len_1, (sizeof(char)));
	// printf("str = %s\n", str);
	if (!str)
		return (NULL);
	// printf("about to JOIN\n");
	str = gnl_join(stash, buff, str);
	// printf("JOIN went OK str is %s\n", str);
	free((void *)stash);
	return (str);
}
