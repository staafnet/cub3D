/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:29:44 by rgrochow          #+#    #+#             */
/*   Updated: 2024/10/27 10:31:24 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	count_lines(const char *map_file)
{
	int		fd;
	char	buf;
	int		line_count;
	ssize_t	bytes_read;

	fd = open(map_file, O_RDONLY);
	line_count = 0;
	while (1)
	{
		bytes_read = read(fd, &buf, 1);
		if (bytes_read <= 0)
			break ;
		if (buf == '\n')
			line_count++;
	}
	close(fd);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0)
		return (line_count + 1);
	else
		return (line_count);
}

char	*read_line(int fd)
{
	char	buffer[1024];
	ssize_t	read_bytes;
	size_t	buffer_pos;
	ssize_t	bytes_read;

	buffer_pos = 0;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		read_bytes = read(fd, &buffer[buffer_pos], 1);
		if (read_bytes <= 0)
			break ;
		if (buffer[buffer_pos] == '\n')
			return (buffer[buffer_pos] = '\0', ft_strdup(buffer));
		buffer_pos++;
		if (buffer_pos >= sizeof(buffer) - 1)
			return (buffer[buffer_pos] = '\0', ft_strdup(buffer));
	}
	if (buffer_pos > 0)
		return (buffer[buffer_pos] = '\0', ft_strdup(buffer));
	return (NULL);
}

int file_exists(const char *path) {
    if (access(path, F_OK) != -1) {
        return 1; // Plik istnieje
    } else {
        printf("Error: File %s does not exist.\n", path);
        return 0; // Plik nie istnieje
    }
}