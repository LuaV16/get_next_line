/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvargas- <lvargas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:57:04 by lvargas-          #+#    #+#             */
/*   Updated: 2025/05/12 01:24:05 by lvargas-         ###   ########.fr       */
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
