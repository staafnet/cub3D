/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:04:52 by rgrochow          #+#    #+#             */
/*   Updated: 2024/11/01 11:06:50 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_direction(t_player *player)
{
	if (player->player_dir == 'N')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
	else if (player->player_dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
	}
	else if (player->player_dir == 'E')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
	else if (player->player_dir == 'W')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
	}
}

static void	init_plane(t_player *player)
{
	if (player->player_dir == 'N')
	{
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else if (player->player_dir == 'S')
	{
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (player->player_dir == 'E')
	{
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (player->player_dir == 'W')
	{
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
}

void	init_player(t_game *game)
{
	printf("%f %f %c\n", game->player.player_x, game->player.player_x, game->player.player_dir);
	init_direction(&game->player);
	init_plane(&game->player);
}
