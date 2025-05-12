/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvargas- <lvargas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:05:18 by lvargas-          #+#    #+#             */
/*   Updated: 2025/05/12 01:28:45 by lvargas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	size_t	n;
	char	*line;

	fd = open("files/empty", O_RDONLY);
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