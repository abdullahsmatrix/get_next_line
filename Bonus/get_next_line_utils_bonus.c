/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamun <amamun@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:26:19 by amamun            #+#    #+#             */
/*   Updated: 2025/11/22 18:20:44 by amamun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1_len;
	size_t		s2_len;
	size_t		i;
	char		*s1_s2_cat;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	s1_s2_cat = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (s1_s2_cat == NULL)
		return (NULL);
	while (*s1 != '\0')
		s1_s2_cat[i++] = *(s1++);
	while (*s2 != '\0')
		s1_s2_cat[i++] = *(s2++);
	s1_s2_cat[i] = '\0';
	return (s1_s2_cat);
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
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (char) c)
			return ((char *) str);
		str++;
	}
	if ((char) c == '\0')
	{
		return ((char *) str);
	}
	return (NULL);
}

