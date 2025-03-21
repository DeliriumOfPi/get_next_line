/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msottana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:47:20 by msottana          #+#    #+#             */
/*   Updated: 2024/11/17 19:35:27 by msottana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#define MAX_SIZE 1024
#include "get_next_line_bonus.h"

static void	update_line(char **line, char *buffer, int read_bytes)
{
	char	*tmp;
	int		size;

	tmp = *line;
	size = ft_strlen(tmp) + read_bytes + 1;
	*line = malloc(size);
	if (!*line)
		return (free(tmp));
	ft_strlcpy(*line, tmp, size);
	ft_strlcat(*line, buffer, size);
	free(tmp);
}

static char	*get_line(char **line)
{
	char	*result;
	char	*next_line;
	char	*tmp;

	if (!**line)
		return (free(*line), line = NULL, NULL);
	next_line = ft_strchr(*line, '\0');
	if (ft_strchr(*line, '\n'))
		next_line = ft_strchr(*line, '\n') + 1;
	result = malloc(next_line - *line + 1);
	if (!result)
		return (free(*line), *line = NULL, NULL);
	ft_strlcpy(result, *line, next_line - *line + 1);
	tmp = ft_strdup(next_line);
	if (!tmp)
		return (free(result), NULL);
	free(*line);
	*line = malloc(ft_strlen(tmp) + 1);
	if (!*line)
		return (free(tmp), free(result), NULL);
	ft_strlcpy(*line, tmp, ft_strlen(tmp) + 1);
	return (free(tmp), result);
}

char	*get_next_line(int fd)
{
	int			read_bytes;
	static char	*line_ar[MAX_SIZE];
	char		*buffer;

	if (!line_ar[fd])
		line_ar[fd] = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(line_ar[fd]), line_ar[fd] = NULL, NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(line_ar[fd]), line_ar[fd] = NULL, NULL);
	while (!ft_strchr(line_ar[fd], '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(line_ar[fd]), free(buffer), line_ar[fd] = NULL, NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		update_line(&line_ar[fd], buffer, read_bytes);
		if (!line_ar[fd])
			return (free(buffer), NULL);
	}
	free(buffer);
	return (get_line(&line_ar[fd]));
}
