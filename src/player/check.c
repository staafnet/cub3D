/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:04:34 by rgrochow          #+#    #+#             */
/*   Updated: 2024/11/01 11:01:40 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_player(t_game *game, char *line, int height)
{
	int	i;	

	i = 0;
	while (i < ft_strlen(line))
	{
		printf("%c", game->player.player_dir);
		if (game->player.player_dir == 'X' && (line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
		{
			game->player.player_dir = line[i];
			game->player.player_x = height + 0.5;
			game->player.player_y = i + 0.5;
		}
		else if (game->player.player_dir != 'X' && (line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
			return (0);
		i++;
	}
	return (1);
}
