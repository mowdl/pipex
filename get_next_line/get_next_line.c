/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:55:33 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/21 23:55:26 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

void	append_to_str(t_string *str, char *buf, ssize_t bytes)
{
	char	*tmp;

	if (str->size <= str->len + bytes + 1)
	{
		str->size = (str->size + bytes) * 2;
		tmp = malloc(sizeof(char) * str->size);
		if (tmp == NULL)
		{
			str->len = 0;
			return ;
		}
		if (str->len)
			ft_memcpy(tmp, str->s, str->len + 1);
		if (str->s)
			free(str->s);
		str->s = tmp;
	}
	ft_memcpy(str->s + str->len, buf, bytes);
	str->len += bytes;
	str->s[str->len] = '\0';
}

void	read_until_endl(int fd, t_string *str, char *buf)
{
	ssize_t	bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		append_to_str(str, buf, bytes);
		if (str->len == 0)
			return ;
		if (ft_memchr(buf, '\n', bytes))
			return ;
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes == -1)
	{
		str->len = 0;
		return ;
	}
}

void	clean_str(t_string *str)
{
	char	*endl;
	size_t	len;

	endl = ft_memchr(str->s, '\n', str->len);
	if (endl == NULL)
	{
		str->len = 0;
		return ;
	}
	len = str->len - (endl + 1 - str->s);
	ft_memcpy(str->s, endl + 1, len);
	str->len = len;
}

char	*get_line_from_string(t_string *str)
{
	char	*line;
	char	*endl;
	size_t	len;

	if (str->len == 0)
		return (NULL);
	endl = ft_memchr(str->s, '\n', str->len);
	if (endl == NULL)
		len = str->len;
	else
		len = endl - str->s + 1;
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, str->s, len);
	line[len] = '\0';
	clean_str(str);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_string	str;
	char			*buf;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	read_until_endl(fd, &str, buf);
	free(buf);
	line = 0;
	if (str.len)
		line = get_line_from_string(&str);
	if (str.len == 0)
	{
		if (str.size)
			free(str.s);
		str.s = 0;
		str.size = 0;
	}
	return (line);
}
