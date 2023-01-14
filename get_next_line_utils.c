/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiovann <egiovann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:02:27 by egiovann          #+#    #+#             */
/*   Updated: 2023/01/14 18:15:56 by egiovann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_calloc(int count, int size)
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

int	ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

static char	*gnl_join(char const *stash,
	char const *buff, char *res, int stash_len)
{
	int		i;
	int		buff_len;

	i = 0;
	buff_len = ft_strlen(buff);
	if (stash != NULL)
	{
		while (i < stash_len)
		{
			res[i] = stash[i];
			i++;
		}
	}
	i = 0;
	if (buff != NULL)
	{
		while (i < buff_len)
		{
			res[stash_len + i] = buff[i];
			i++;
		}
	}
	res[stash_len + i] = '\0';
	return (res);
}

char	*gnl_join_n_free(char const *stash, char const *buff)
{
	int		stash_len;
	int		buff_len;
	char	*res;

	stash_len = gnl_strlen(stash);
	buff_len = gnl_strlen(buff);
	res = (char *)malloc(sizeof(char) * (stash_len + buff_len + 1));
	if (!stash)
		// malloc (stash * 1) = '\0'
	if (!res )
		return (NULL);
	res = gnl_join(stash, buff, res, stash_len);
	free((void *)stash);
	free((void *)buff);
	return (res);
}

