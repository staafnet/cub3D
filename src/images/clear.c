/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:58:40 by rgrochow          #+#    #+#             */
/*   Updated: 2024/10/19 17:00:46 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clear_images(t_game *game)
{
    free(game->image.north_texture);
    free(game->image.south_texture);
    free(game->image.west_texture);
    free(game->image.east_texture);
    }