/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:38:31 by rgrochow          #+#    #+#             */
/*   Updated: 2024/10/27 11:15:45 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

/*

void my_mlx_pixel_put(t_game *game, int x, int y, int color) {
    char *dst;

    dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void render_raycasting(t_game *game) {
    for (int x = 0; x < WIN_WIDTH; x++) {
        double cameraX = 2 * x / (double)WIN_WIDTH - 1;
        double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
        double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

        int mapX = (int)game->player.x;
        int mapY = (int)game->player.y;

        double sideDistX, sideDistY;
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX, stepY;
        int hit = 0;
        int side;

        // Initialize side distance and step direction
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (game->player.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (game->player.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
        }

        // Raycasting loop
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->map[mapX][mapY] > 0) hit = 1; // Hit a wall
        }

        // Calculate distance to the wall
        if (side == 0)
            perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / rayDirY;

        // Calculate the height of the line to draw
        int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        // Set color based on side hit
        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

        // Draw the vertical line for the wall
        for (int y = drawStart; y < drawEnd; y++) {
            my_mlx_pixel_put(game, x, y, color);
        }

        // Draw the floor below the wall
        for (int y = drawEnd; y < WIN_HEIGHT; y++) {
            my_mlx_pixel_put(game, x, y, game->floor_color);
        }

        // Draw the ceiling above the wall
        for (int y = 0; y < drawStart; y++) {
            my_mlx_pixel_put(game, x, y, game->ceiling_color);
        }
    }
}

void move_player(t_game *game) {
    double newX = game->player.x;
    double newY = game->player.y;

    if (game->key_states[122]) { // W key
        printf("W pressed, moving forward\n");
        newX += game->player.dir_x * MOVE_SPEED;
        newY += game->player.dir_y * MOVE_SPEED;
        printf("New position: %f, %f\n", newX, newY);
    }
    if (game->key_states[115]) { // S key
        printf("S pressed, moving backward\n");
        newX -= game->player.dir_x * MOVE_SPEED;
        newY -= game->player.dir_y * MOVE_SPEED;
        printf("New position: %f, %f\n", newX, newY);
    }

    game->player.x = newX;
    game->player.y = newY;
    // Handle rotation (A and D keys)
    if (game->key_states[100]) { // D key
        double oldDirX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
        game->player.dir_y = oldDirX * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
        double oldPlaneX = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
        game->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
    }
    if (game->key_states[113]) { // A key
        double oldDirX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = oldDirX * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
        double oldPlaneX = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
        game->player.plane_y = oldPlaneX * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
    }
}

int key_press(int keycode, t_game *game) {
    printf("Key pressed: %d\n", keycode);
    game->key_states[keycode] = 1;
    return 0;
}

int key_release(int keycode, t_game *game) {
    game->key_states[keycode] = 0;
    return 0;
}



// Now the loop function needs to match the expected prototype
int loop(t_game *game) {
    move_player(game);
    //render_raycasting(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
    return 0; // Return type should match the expected prototype
}

void parse_file(char *file_path, t_game *game) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Error: Cannot open file\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int map_row = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "F ", 2) == 0) {
            int r, g, b;
            sscanf(line + 2, "%d,%d,%d", &r, &g, &b);
            game->floor_color = (r << 16) | (g << 8) | b;
        } else if (strncmp(line, "C ", 2) == 0) {
            int r, g, b;
            sscanf(line + 2, "%d,%d,%d", &r, &g, &b);
            game->ceiling_color = (r << 16) | (g << 8) | b;
        } else if (isdigit(line[0])) {
            for (int i = 0; i < MAP_WIDTH && line[i] != '\0'; i++) {
                if (line[i] == ' ')
                    continue;
                game->map[map_row][i] = line[i] - '0';
            }
            map_row++;
        }
    }

    fclose(file);
}
*/

static void	check_args(int argc)
{
	if (argc != 2)
	{
		printf("Usage: ./cub3D <map_file>\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc);
	check_map_file(&game, argv[1]);
	init_map_file(&game, argv[1]);
	check_map(&game);
	init_player(&game);
	game.mlx = mlx_init();
	check_game(&game);
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
        	/*
    game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
    game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_length, &game.endian);

    game.player.dir_x = -1.0;
    game.player.dir_y = 0.0;
    game.player.plane_x = 0.0;
    game.player.plane_y = 0.66;

    

    mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
    mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game);
    
    mlx_loop_hook(game.mlx, loop, &game);
    
	*/
    clear_map(&game);
    clear_images(&game);
    mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
    return 0;
}
