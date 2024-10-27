/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:05:38 by rgrochow          #+#    #+#             */
/*   Updated: 2024/10/27 11:11:16 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_color(int *color, char *line)
{
	int		r;
	int		g;
	int		b;
	char	*ptr;

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
	*color = (r << 16) | (g << 8) | b;
}

static void	init_map(t_game *game, int n, char *line)
{
	int	i;

	i = 0;
	if (n == 0 || n == game->map.height)
	{
		game->map.grid[n] = malloc(sizeof(char) * (game->map.width + 1));
		if (!game->map.grid[n])
			return ;
		while (i < game->map.width)
		{
			game->map.grid[n][i++] = 'o';
		}
		game->map.grid[n][i++] = '\0';
	}
	n++;
	game->map.grid[n] = malloc(sizeof(char) * (game->map.width + 1));
	if (!game->map.grid[n])
		return ;
	i = 1;
	game->map.grid[n][0] = 'o';
	while (i < game->map.width)
	{
		if (i > ft_strlen(line))
			game->map.grid[n][i] = 'o';
		else
			game->map.grid[n][i] = line[i - 1];
		i++;
	}
	game->map.grid[n][i] = '\0';

}

static void	init_line(t_game *game, char *line, int i)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && i == 0)
		game->image.north_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0 && i == 1)
		game->image.south_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0 && i == 2)
		game->image.west_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0 && i == 3)
		game->image.east_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0 && i == 5)
		init_color(&game->image.floor_color, line);
	else if (ft_strncmp(line, "C ", 2) == 0 && i == 6)
		init_color(&game->image.ceiling_color, line);
	if (i > 7)
	{
		init_map(game, i - 8, line);
	}
}

static void	init_lines(t_game *game, int lines, char *map_file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	i = 0;
	while (i < lines)
	{
		line = read_line(fd);
		init_line(game, line, i);
		free(line);
		i++;
	}
	game->map.grid[game->map.height - 1] = ft_strdup(game->map.grid[0]);
	close(fd);
}

void	init_map_file(t_game *game, char *map_file)
{
	int		lines;
	int		i;

	i = 0;
	lines = count_lines(map_file);
	game->map.height = lines - 6;
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return ;
	init_lines(game, lines, map_file);
	if (!file_exists(game->image.north_texture)
		|| !file_exists(game->image.south_texture)
		|| !file_exists(game->image.west_texture)
		|| !file_exists(game->image.east_texture))
		close_game(game);
	while (i < game->map.height)
	{
		printf("%s\n", game->map.grid[i++]);
	}
}
