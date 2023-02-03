/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daddy_cool <daddy_cool@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:02:27 by egiovann          #+#    #+#             */
/*   Updated: 2023/01/29 02:40:47 by daddy_cool       ###   ########.fr       */
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

	printf("on est dans STRCHR\n");
	i = 0;
	if (s == NULL)
	{
		printf("stash n'existe pas encore\n");
		return (-1);
	}
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			printf("ca y est on a trouvé le 'c' cherché a %d\n", i);
			return (i);
		}
		i++;
	}
	if (s[i] == c)
	{
		printf("s[i] ==== /o\n");
		return (i);
	}
	printf("on n'a pas trouvé de \\n\n");
	return (-1);
}

// int	GGgnl_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	if (c == '\0')
// 		return ((char *)&s[gnl_strlen(s)]);
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (char) c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	return (0);
// }

//TOSH VERSION
// int	gnl_strchr(const char *s, char c)
// {
// 	int		i;

// 	i = 0;
// 	if (s == NULL)
// 		printf("il n'y a rien laaa\n");
// 		return (-1);
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	if (s[i] == c)
// 		return (i);
// 	return (-1);
// }

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
	printf("STR J_N_FREE was : ''%s''\n", str);
	free((void *)stash);
	// free((void *)buff);
	return (str);
}

