/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamun <amamun@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:56:43 by amamun            #+#    #+#             */
/*   Updated: 2025/11/24 18:15:51 by amamun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_new_line(char **stash)
{
	char	*new_line_pos;
	char	*line;
	char	*leftover;

	if (!stash || !*stash)
		return (NULL);
	new_line_pos = ft_strchr(*stash, '\n');
	if (new_line_pos)
	{
		line = ft_substr(*stash, 0, new_line_pos - *stash + 1);
		leftover = ft_strdup(new_line_pos + 1);
		free(*stash);
		*stash = leftover;
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

char	*read_join(int fd, char **stash, char *buf)
{
	ssize_t		num_read;
	char		*temp;

	while (*stash && !(ft_strchr(*stash, '\n')))
	{
		num_read = read (fd, buf, BUFFER_SIZE);
		if (num_read <= 0)
		{
			if (num_read < 0)
			{
				free(*stash);
				*stash = NULL;
			}
			return (*stash);
		}
		buf[num_read] = '\0';
		temp = ft_strjoin(*stash, buf);
		*stash = temp;
		if (!*stash)
			return (NULL);
	}
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FILES];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = malloc(1);
		if (!(stash[fd]))
			return (free(buf), NULL);
		stash[fd][0] = '\0';
	}
	stash[fd] = read_join(fd, &stash[fd], buf);
	free(buf);
	if (!stash[fd] || *stash[fd] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	return (extract_new_line(&stash[fd]));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	char	titles[3][20] = {"poem.txt", "poem 2.txt", "poem 3.txt"};

// 	for (int i = 0; i < 3; i++)
// 	{
// 		fd = open(titles[i], O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror("open");
// 			return (1);
// 		}
// 		line = get_next_line(fd);
// 		while (line)
// 		{
// 			printf("%s", line);
// 			free(line);
// 			line = get_next_line(fd);
// 		}
// 		close(fd);
// 	}
// 	return (0);
// }