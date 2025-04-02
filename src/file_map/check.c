/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:09:15 by rgrochow          #+#    #+#             */
/*   Updated: 2025/01/05 22:27:25 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_color(char *line)
{
	int		r;
	int		g;
	int		b;
	char	*ptr;
    int     comma;

    comma = 0;
	ptr = line + 2;
    while (*ptr)
    {
        if (*ptr == ',')
        {
            comma++;
            if (!*(ptr - 1) || !*(ptr + 1))
                return 0;

            if ((*(ptr - 1) < '0' || *(ptr - 1) > '9')
                || (*(ptr + 1) < '0' || *(ptr + 1) > '9'))
            {
                return 0;
            }
        }
        if ((*ptr >= '0' && *ptr <= '9') || *ptr == ',')
            ptr++;
        else
            return (0);
    }
    if (comma != 2)
        return 0;
    ptr = line + 2;
    r = 0;
	g = 0;
	b = 0;
	while (*ptr >= '0' && *ptr <= '9')
	{
		r = r * 10 + (*ptr - '0');
		ptr++;
	}
    ptr++;
	while (*ptr >= '0' && *ptr <= '9')
	{
		g = g * 10 + (*ptr - '0');
		ptr++;
	}
    ptr++;
	while (*ptr >= '0' && *ptr <= '9')
	{
		b = b * 10 + (*ptr - '0');
		ptr++;
	}
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (0);
	return (1);
}

static int	check_line(char *line, int i)
{
	if ((ft_strncmp(line, "NO ", 3) != 0 && i == 0)
		|| (ft_strncmp(line, "SO ", 3) != 0 && i == 1)
		|| (ft_strncmp(line, "WE ", 3) != 0 && i == 2)
		|| (ft_strncmp(line, "EA ", 3) != 0 && i == 3)
		|| (ft_strncmp(line, "F ", 2) != 0 && i == 5)
		|| (ft_strncmp(line, "C ", 2) != 0 && i == 6))
		return (0);
	else if (i > 7)
	{
		while (*line)
		{
			if (*line == ' ' || *line == '\n' || *line == '0' || *line == '1'
				|| *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			{
				line++;
				continue ;
			}
			else
			{
				return (0);
			}
		}
	}
	return (1);
}

static int	check_lines(int lines, char *map_file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	i = 0;
	while (i < lines)
	{
		line = read_line(fd);
		if (!line)
		{
			i++;
			continue ;
		}
		(free(line), i++);
	}
	fd = open(map_file, O_RDONLY);
	i = 0;
	while (i < lines)
	{
		line = read_line(fd);
		if (!line)
		{
			i++;
			continue ;
		}
		if (!check_line(line, i))
			return (close(fd), free(line), 0);
		if (i == 5 || i == 6)
			if (!check_color(line))
				return (close(fd), free(line), 0);
		(free(line), i++);
	}
	return (close(fd), 1);
}

void	check_map_file(char *map_file)
{
    int		fd;
	int		lines;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		(printf("File not found: %s\n", map_file), exit(0));
	lines = count_lines(map_file);
	if (lines < 11)
		(close(fd), printf("Error map file\n"), exit(0));
	close(fd);
    if (!check_lines(lines, map_file))
		(printf("Error map structure\n"), exit(0));
}
