/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:36:42 by rgrochow          #+#    #+#             */
/*   Updated: 2024/10/27 10:39:31 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_images(t_game *game)
{
    game->image.img = mlx_xpm_file_to_image(game->mlx, game->image.north_texture, &width, &height);
    game->image.south = NULL;
    game->image.west = NULL;
    game->image.east = NULL;
    game->image.floor = NULL;
    game->image.ceiling = NULL;
}