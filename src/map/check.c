/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:33:13 by rgrochow          #+#    #+#             */
/*   Updated: 2024/11/01 16:21:55 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
static int	**init_visited(t_game *game)
{
	int	**visited;
	int	i;
	int	j;

	visited = malloc((game->map.height + 3) * sizeof(int *));
	if (!visited)
		close_game(game);
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = malloc((game->map.width + 3) * sizeof(int));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			close_game(game);
		}
		j = 0;
		while (j < game->map.width)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

static int	**init_directions(void)
{
	int			i;
	static int	directions[4][2];
	static int	*dir[4];

	directions[0][0] = 0;
	directions[0][1] = 1;
	directions[1][0] = 0;
	directions[1][1] = -1;
	directions[2][0] = 1;
	directions[2][1] = 0;
	directions[3][0] = -1;
	directions[3][1] = 0;
	i = 0;
	while (i < 4)
	{
		dir[i] = directions[i];
		i++;
	}
	return (dir);
}

static int	is_access(t_game *game)
{
	int	**directions;
	int	**visited;
	int	valid;
	int	i;

	valid = 0;
	directions = init_directions();
	visited = init_visited(game);
	if (bfs(game, directions, visited))
		valid = 1;
	i = 0;
	while (i < game->map.height)
		free(visited[i++]);
	free(visited);
	return (valid);
}

void	check_map(t_game *game)
{
	int	i;

	i = 0;
	game->player.player_dir = 'X';
	while (i < game->map.height)
	{
		printf("%s\n", game->map.grid[i++]);
	}
	i = 0;
	game->player.player_x = 0;
	game->player.player_y = 0;
	while (i < game->map.height)
	{
		if (!check_player(game, game->map.grid[i], i))
		{
			close_game(game);
		}
		i++;
	}
	if (game->player.player_dir == 'X' || !is_access(game))
	{
		close_game(game);
	}
}
*/