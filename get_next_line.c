/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvargas- <lvargas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:35 by lvargas-          #+#    #+#             */
/*   Updated: 2025/05/06 16:20:11 by lvargas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*next_line;
	size_t		n;
	size_t		line_size;
	size_t		i;
	size_t	save;
	size_t	bytes_read;
	int	found_new_line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer || fd == -1)
		return (NULL);
	found_new_line = 0;
	while (!found_new_line && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		rest = ft_strjoin(rest, buffer);
		if (ft_strchr(rest, '\n'))
			found_new_line = 1;
	}
	if (bytes_read == 0)
		return (NULL);
	n = 0;
	line_size = 0;
	if (rest)
	{
		while (rest[n++] != '\0')
			line_size++;
	}
	n = 0;
	while (buffer[n] != '\0' && buffer[n++] != '\n')
		line_size++;
	next_line = malloc((line_size + 1) * sizeof(char));
	i = 0;
	if (rest)
	{
		while (rest[i] != '\0')
		{
			next_line[i] = rest[i];
			i++;
		}
	}
	n = 0;
	while (buffer[n] != '\n' && buffer[n] != '\0')
	{
		next_line[i + n] = buffer[n];
		n++;
	}
	next_line[i + n] = '\0';
	i = 0;
	if (buffer[n] != '\0')
	{
		n++;
		free(rest);
		line_size = 0;
		save = n;
		while (buffer[save] != '\0')
		{
			line_size++;
			save++;
		}
		rest = malloc((line_size + 1) * sizeof(char));
		while (buffer[n] != '\0')
		{
			rest[i] = buffer[n];
			i++;
			n++;
		}
		rest[i] = '\0';
	}
	return (next_line);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	n = 0;
	size_t	i = 0;
	size_t	len1 = 0;
	size_t	len2 = 0;
	char	*ptr;

	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	ptr = malloc((len1 + len2 + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1 && s1[n])
	{
		ptr[n] = s1[n];
		n++;
	}
	while (s2 && s2[i])
	{
		ptr[n + i] = s2[i];
		i++;
	}
	ptr[n + i] = '\0';
	return (ptr);
}


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

int main(void)
{
    int fd = open("files/multiple_line_no_nl", O_RDONLY);
    size_t n = 1;
	char *line;

	line = get_next_line(fd);
    while (line != NULL)
    {
        printf("Line %zu: %s\n", n, line);
        n++;
		line = get_next_line(fd);
    }
    
    return 0;
}
