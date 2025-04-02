/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:29:36 by rgrochow          #+#    #+#             */
/*   Updated: 2025/01/05 23:43:43 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error(char *status, void *data)
{
	if (ft_strcmp(status, "USAGE") == 0)
		(printf("Usage: ./cub3D maps/<map_file>\n"), exit(0));
	else if (ft_strcmp(status, "MAP_FILE_NOT_FOUND") == 0)
        (printf("File not found: %s\n", (char *)data), exit(0));
    else if (ft_strcmp(status, "ERROR_MAP_FILE") == 0)
    {
        close_game(data);
    }
    else
    {
        printf("Unknown error status: %s\n", status);
    }
}
