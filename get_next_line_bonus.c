/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvargas- <lvargas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:47:47 by lvargas-          #+#    #+#             */
/*   Updated: 2025/05/09 16:55:19 by lvargas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_new_line(char *total_line)
{
	char	*new_line;
	size_t	n;

	n = 0;
	while (total_line[n] != '\n' && total_line[n] != '\0')
		n++;
	if (total_line[n] == '\n')
		n++;
	new_line = malloc((n + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	n = 0;
	while (total_line[n] != '\n' && total_line[n] != '\0')
	{
		new_line[n] = total_line[n];
		n++;
	}
	if (total_line[n] == '\n')
	{
		new_line[n] = total_line[n];
		n++;
	}
	new_line[n] = '\0';
	return (new_line);
}

void	fill_buffer(char *total_line, char **buffer)
{
	size_t	n;
	size_t	i;
	size_t	remaining_len;

	n = 0;
	while (total_line[n] != '\n' && total_line[n] != '\0')
		n++;
	if (total_line[n] == '\n')
		n++;
	remaining_len = ft_strlen(total_line + n);
	if (*buffer)
		free(*buffer);
	*buffer = (char *)malloc((remaining_len + 1) * sizeof(char));
	if (!*buffer)
		return ;
	i = 0;
	while (total_line[n + i] != '\0')
	{
		(*buffer)[i] = total_line[i + n];
		i++;
	}
	(*buffer)[i] = '\0';
}

char	*read_until_new_line(int fd, char *total_line, char **new_read)
{
	char	*tmp;
	ssize_t	bytes_read;

	while (1)
	{
		tmp = total_line;
		total_line = ft_strjoin(tmp, *new_read);
		free(tmp);
		free(*new_read);
		*new_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!*new_read)
			break ;
		if (ft_strchr(total_line, '\n'))
			break ;
		bytes_read = read(fd, *new_read, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		if (bytes_read > 0)
			(*new_read)[bytes_read] = '\0';
	}
	return (total_line);
}

char	*prepare_line(int fd, char *buffer)
{
	char	*new_read;
	char	*total_line;
	ssize_t	bytes_read;

	if (buffer && ft_strchr(buffer, '\n'))
		return (ft_strdup(buffer));
	new_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_read)
		return (NULL);
	bytes_read = read(fd, new_read, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(new_read), NULL);
	if (bytes_read == 0)
		return (free(new_read), ft_strdup(buffer));
	new_read[bytes_read] = '\0';
	if (buffer)
		total_line = ft_strdup(buffer);
	else
		total_line = ft_strdup("");
	total_line = read_until_new_line(fd, total_line, &new_read);
	free(new_read);
	return (total_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[2048];
	char		*new_line;
	char		*total_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 2048)
		return (NULL);
	total_line = prepare_line(fd, buffer[fd]);
	if (!total_line || ft_strlen(total_line) == 0)
	{
		free(total_line);
		if (buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	new_line = get_new_line(total_line);
	fill_buffer(total_line, &buffer[fd]);
	free(total_line);
	return (new_line);
}
