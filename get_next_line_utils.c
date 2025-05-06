/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvargas- <lvargas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:32:23 by lvargas-          #+#    #+#             */
/*   Updated: 2025/05/06 16:13:37 by lvargas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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