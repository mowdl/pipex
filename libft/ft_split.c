/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:07:00 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 23:56:37 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		words++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	**free_arr(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	size_t	wlen;
	size_t	i;
	char	**arr;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	arr = ft_calloc(sizeof(char **), words + 1);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		wlen = word_len(s, c);
		arr[i] = ft_substr(s, 0, wlen);
		if (arr[i] == NULL)
			return (free_arr(arr, i));
		s += wlen;
		i++;
	}
	return (arr);
}
