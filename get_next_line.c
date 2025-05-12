/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvargas- <lvargas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:43:16 by lvargas-          #+#    #+#             */
/*   Updated: 2025/05/12 02:00:32 by lvargas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strdup(char *s)
{
	size_t	n;
	char	*ptr;

	n = 0;
	ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[n])
	{
		ptr[n] = (char)s[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	n;
	size_t	i;
	char	*ptr;

	n = 0;
	i = 0;
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[n] != '\0')
	{
		ptr[n] = (char)s1[n];
		n++;
	}
	while (s2[i] != '\0')
	{
		ptr[n] = (char)s2[i];
		i++;
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c && *s)
	{
		s++;
	}
	if (*s == '\0')
	{
		if ((unsigned char)c == '\0')
			return ((char *)s);
		else
			return (NULL);
	}
	return ((char *)s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	n;

	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	n = 0;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (n < len)
	{
		substr[n] = s[start];
		start++;
		n++;
	}
	substr[n] = '\0';
	return (substr);
}

char	*safe_strjoindub(char *s1, char *s2, int n)
{
	char	*result;

	if (n == 0)
	{
		result = ft_strdup(s2);
		if (!result)
			return (NULL);
	}
	else if (n == 1)
	{
		result = ft_strjoin(s1, s2);
		if (!result)
		{
			free(s1);
			return (NULL);
		}
		free(s1);
	}
	else
		return (NULL);
	return (result);
}

ssize_t	get_total_line(int fd, char **total_line)
{
	char	*new_read;
	ssize_t	bytes_read;

	while (1)
	{
		new_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!new_read)
			return (free(new_read), 0);
		bytes_read = read(fd, new_read, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free(new_read), bytes_read);
		new_read[bytes_read] = '\0';
		if (!*total_line)
			*total_line = safe_strjoindub(NULL, new_read, 0);
		else
			*total_line = safe_strjoindub(*total_line, new_read, 1);
		free(new_read);
		if (ft_strchr(*total_line, '\n'))
			break ;
	}
	return (bytes_read);
}

char	*get_new_line(char **total_line, char **buffer)
{
	char	*new_line;
	char	*temp;
	size_t	n;

	if (buffer && *buffer && **buffer && *total_line != NULL)
	{
		temp = *total_line;
		*total_line = ft_strjoin(*buffer, *total_line);
		free(temp);
		free(*buffer);
	}
	if (*total_line == NULL && *buffer)
		*total_line = safe_strjoindub(NULL, *buffer, 0);
	n = 0;
	while ((*total_line)[n] && (*total_line)[n] != '\n')
		n++;
	if ((*total_line)[n] == '\n')
		n++;
	new_line = ft_substr(*total_line, 0, n);
	return (new_line);
}

char	*fill_buffer(char *total_line)
{
	char	*buffer;
	size_t	n;

	n = 0;
	if (total_line == NULL)
		return (NULL);
	while (total_line[n] && total_line[n] != '\n')
		n++;
	if (total_line[n] == '\n')
		n++;
	else if (total_line[n] == '\0')
		return (NULL);
	buffer = ft_substr(total_line, n, ft_strlen(total_line));
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*total_line;
	char		*new_line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	total_line = NULL;
	bytes_read = get_total_line(fd, &total_line);
	if (!total_line && !buffer)
		return (free(total_line), NULL);
	if (bytes_read == -1)
		return (free(buffer), free(total_line), NULL);
	if (bytes_read == 0 && *buffer == '\0')
		return (free(buffer), buffer = NULL, NULL);
	new_line = get_new_line(&total_line, &buffer);
	free(buffer);
	buffer = fill_buffer(total_line);
	free(total_line);
	return (new_line);
}

int	main(void)
{
	int		fd;
	size_t	n;
	char	*line;

	fd = open("files/41_with_nl", O_RDONLY);
	n = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Line %zu: %s", n, line);
		n++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}