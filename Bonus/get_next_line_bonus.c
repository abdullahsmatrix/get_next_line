/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamun <amamun@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:26:38 by amamun            #+#    #+#             */
/*   Updated: 2025/11/22 18:21:31 by amamun           ###   ########.fr       */
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

char	*read_join(int fd, char *stash, char *buf)
{
	ssize_t		num_read;
	char		*temp;

	num_read = 0;
	while (!stash || !(ft_strchr(stash, '\n')))
	{
		num_read = read (fd, buf, BUFFER_SIZE);
		if (num_read <= 0)
		{
			if (num_read == 0)
				break ;
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[num_read] = '\0';
		temp = ft_strjoin(stash, buf);
		free(stash);
		stash = temp;
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*buf;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);

	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	stash[fd] = read_join(fd, stash[fd], buf);
	if (!stash[fd])
		return (NULL);
	return (extract_new_line(&stash[fd]));
}

int	main(void)
{
	int		fd;
	int 	fd2;
	int		fd3;
	char	*line;

	fd2 = open("poem 2.txt", O_RDONLY);
	fd3 = open("poem 3.txt", O_RDONLY);
	fd = open("poem.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open1");
		return (1);
	}
	if (fd2 == -1)
	{
		perror("open2");
		return (1);
	}
	if (fd3 == -1)
	{
		perror("open2");
		return (1);
	}
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd3);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
	close(fd2);
	close(fd3);
	
	// while (line)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// }
	return (0);
}