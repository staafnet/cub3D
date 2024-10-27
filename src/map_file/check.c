/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:09:15 by rgrochow          #+#    #+#             */
/*   Updated: 2024/10/27 12:00:01 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_color(char *line, int i)
{
	int		r;
	int		g;
	int		b;
	char	*ptr;

	(void)i;
	r = 0;
	g = 0;
	b = 0;
	ptr = line + 2;
	while (*ptr >= '0' && *ptr <= '9')
	{
		r = r * 10 + (*ptr - '0');
		ptr++;
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		ptr++;
		g = g * 10 + (*ptr - '0');
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		ptr++;
		b = b * 10 + (*ptr - '0');
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

static int	check_lines(t_game *game, int lines, char *map_file)
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
		if (ft_strlen(line) > game->map.width)
			game->map.width = ft_strlen(line) + 2;
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
			if (!check_color(line, i))
				return (close(fd), free(line), 0);
		(free(line), i++);
	}
	return (close(fd), 1);
}

void	check_map_file(t_game *game, char *map_file)
{
	int		fd;
	int		lines;

	game->map.width = 0;
	fd = open(map_file, O_RDONLY);
	lines = count_lines(map_file);
	if (fd == -1 || lines < 11)
	{
		printf("Error map file\n");
		exit(0);
	}
	close(fd);
	if (!check_lines(game, lines, map_file))
	{
		printf("Error map structure\n");
		exit(0);
	}
}
