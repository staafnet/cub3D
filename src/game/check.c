/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:11:36 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/29 13:11:54 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_game(t_game *game)
{
	if (!game->mlx)
	{
		printf("Error: Failed to initialize XML\n");
		exit(0);
	}
}
