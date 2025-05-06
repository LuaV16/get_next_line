/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvargas- <lvargas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:35 by lvargas-          #+#    #+#             */
/*   Updated: 2025/05/06 21:25:00 by lvargas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
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

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*next_line;
	char	*new_read;
	size_t		n;
	size_t		line_size;
	size_t		i;
	size_t	save;
	size_t	bytes_read;
	int	found_new_line;

	new_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_read || fd == -1)
		return (NULL);
	found_new_line = 0;
	buffer = rest;
	while (!found_new_line && (bytes_read = read(fd, new_read, BUFFER_SIZE)) > 0)
	{
		new_read[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, new_read);
		if (ft_strchr(buffer, '\n'))
			found_new_line = 1;
	}
	if (bytes_read == 0 && buffer && *buffer != '\0')
	{
		next_line = ft_strdup(buffer);
		rest = NULL;
		return (next_line);
	}
	if (bytes_read == 0)
		return (NULL);
	n = 0;
	line_size = 0;
	while (buffer[n] != '\0' && buffer[n] != '\n')
	{
		line_size++;
		n++;
	}
	next_line = malloc((line_size + 1) * sizeof(char));
	n = 0;
	while (buffer[n] != '\n' && buffer[n] != '\0')
	{
		next_line[n] = buffer[n];
		n++;
	}
	next_line[n] = '\0';
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
		i = 0;
		while (buffer[n] != '\0')
		{
			rest[i] = buffer[n];
			i++;
			n++;
		}
		free(buffer);
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
    int fd = open("files/alternate_line_nl_with_nl", O_RDONLY);
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
