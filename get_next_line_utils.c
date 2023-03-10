/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 03:42:24 by daddy_cool        #+#    #+#             */
/*   Updated: 2023/01/29 03:43:43 by daddy_cool       ###   ########.fr       */
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
		i++;
	return (i);
}

char	*gnl_calloc(int count, int size)
{
	char	*ptr;
	int		i;

	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int		gnl_strchr(const char *s, char c)
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
		i++;
	}
	if (s[i] == c)
	{
		return (i);
	}
	return (-1);
}

static char	*gnl_join(char const *stash, char const *buff, char *str)
{
	int		i;
	int		buff_len;
	int		stash_len;

	i = 0;
	buff_len = gnl_strlen(buff);
	stash_len = gnl_strlen(stash);
	if (stash != NULL)
	{
		while (i < stash_len)
		{
			str[i] = stash[i];
			i++;
		}
	}
	i = 0;
	if (buff != NULL)
	{
		while (i < buff_len)
		{
			str[stash_len + i] = buff[i];
			i++;
		}
	}
	str[stash_len + i] = '\0';
	return (str);
}

char	*gnl_join_n_free(char const *stash, char const *buff)
{
	char	*str;

	str = (char *)gnl_calloc((sizeof(char)), (gnl_strlen(stash) + (gnl_strlen(buff)) + 1));
	if (!str)
		return (NULL);
	str = gnl_join(stash, buff, str);
	free((void *)stash);
	return (str);
}
