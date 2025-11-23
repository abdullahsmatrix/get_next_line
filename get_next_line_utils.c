/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamun <amamun@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:12:41 by amamun            #+#    #+#             */
/*   Updated: 2025/11/23 21:05:29 by amamun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t i;
    size_t j;
    char *cat;

	i = 0;
	j = 0;
    if (!s1)
        return ft_strdup(s2);
    if (!s2)
        return ft_strdup(s1);
    cat = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!cat)
        return NULL;
    while (s1[i])
    {
        cat[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        cat[i + j] = s2[j];
        j++;
    }
    cat[i + j] = '\0';
    free(s1);
    return cat;
}

int	ft_strlen(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		i++;
	}
	return ((int)i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	j;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	j = 0;
	substr = (char *) malloc(len * sizeof(char) + 1);
	if (!substr)
		return (NULL);
	while (s[start] && j < len)
	{
		substr[j] = s[start];
		start++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

char	*ft_strdup(const char *str)
{
	char		*dup;
	size_t		len;
	size_t		i;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = (char *) malloc(len + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char) c)
			return ((char *) str);
		str++;
	}
	return (NULL);
}

