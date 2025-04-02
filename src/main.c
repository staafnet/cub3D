/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:38:31 by rgrochow          #+#    #+#             */
/*   Updated: 2025/02/24 22:46:59 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"
/*
void    my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    if (y < 0 || y >=  game->screen_height || x < 0 || x >= game->screen_width)
        return;
    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    draw_frame(t_game *game)
{
    int x;
    for (x = 0; x < game->screen_width; x++)
    {
        double cameraX = 2 * x / (double)game->screen_width - 1;
        double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
        double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
        int mapX = (int)game->player.player_x;
        int mapY = (int)game->player.player_y;
        double sideDistX;
        double sideDistY;
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;
        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.player_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.player_x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.player_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.player_y) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->map.grid[mapX][mapY] == '1')
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - game->player.player_x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->player.player_y + (1 - stepY) / 2) / rayDirY;

        int line game->screen_height = (int)( game->screen_height / perpWallDist);

        int drawStart = -line game->screen_height / 2 +  game->screen_height / 2 + (int)game->pitch;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = line game->screen_height / 2 +  game->screen_height / 2 + (int)game->pitch;
        if (drawEnd >=  game->screen_height)
            drawEnd =  game->screen_height - 1;

        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;
        
        for (int y = 0; y < drawStart; y++)
        {
            my_mlx_pixel_put(game, x, y, 0x87CEEB);
        }

        for (int y = drawStart; y < drawEnd; y++)
        {
            my_mlx_pixel_put(game, x, y, color);
        }

        for (int y = drawEnd; y <  game->screen_height; y++)
        {
            my_mlx_pixel_put(game, x, y, 0x228B22);
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void    move_player(t_game *game)
{
    if (game->move_forward)
    {
        if (game->map.grid[(int)(game->player.player_x + game->player.dir_x * MOVE_SPEED)][(int)game->player.player_y] == '0')
            game->player.player_x += game->player.dir_x * MOVE_SPEED;
        if (game->map.grid[(int)game->player.player_x][(int)(game->player.player_y + game->player.dir_y * MOVE_SPEED)] == '0')
            game->player.player_y += game->player.dir_y * MOVE_SPEED;
    }
    if (game->move_backward)
    {
        if (game->map.grid[(int)(game->player.player_x - game->player.dir_x * MOVE_SPEED)][(int)game->player.player_y] == '0')
            game->player.player_x -= game->player.dir_x * MOVE_SPEED;
        if (game->map.grid[(int)game->player.player_x][(int)(game->player.player_y - game->player.dir_y * MOVE_SPEED)] == '0')
            game->player.player_y -= game->player.dir_y * MOVE_SPEED;
    }
    if (game->move_right)
    {
        if (game->map.grid[(int)(game->player.player_x + game->player.plane_x * MOVE_SPEED)][(int)game->player.player_y] == '0')
            game->player.player_x += game->player.plane_x * MOVE_SPEED;
        if (game->map.grid[(int)game->player.player_x][(int)(game->player.player_y + game->player.plane_y * MOVE_SPEED)] == '0')
            game->player.player_y += game->player.plane_y * MOVE_SPEED;
    }
    if (game->move_left)
    {
        if (game->map.grid[(int)(game->player.player_x - game->player.plane_x * MOVE_SPEED)][(int)game->player.player_y] == '0')
            game->player.player_x -= game->player.plane_x * MOVE_SPEED;
        if (game->map.grid[(int)game->player.player_x][(int)(game->player.player_y - game->player.plane_y * MOVE_SPEED)] == '0')
            game->player.player_y -= game->player.plane_y * MOVE_SPEED;
    }
}

int key_press(int key, t_game *game)
{
    if (key == 65507) // ESC key
    {
        mlx_mouse_show(game->mlx, game->win);
    }
    if (key == 65307) // ESC key
    {
        exit(0);
    }
    if (key == 122) // W key
        game->move_forward = 1;
    if (key == 115) // S key
        game->move_backward = 1;
    if (key == 113) // A key
        game->move_left = 1;
    if (key == 100) // D key
        game->move_right = 1;
    return (0);
}

int key_release(int key, t_game *game)
{
    if (key == 65507) // ESC key
    {
        mlx_mouse_hide(game->mlx, game->win);
    }
    if (key == 122) // W key
        game->move_forward = 0;
    if (key == 115) // S key
        game->move_backward = 0;
    if (key == 113) // A key
        game->move_left = 0;
    if (key == 100) // D key
        game->move_right = 0;
    return (0);
}

int mouse_move(int x, int y, t_game *game)
{
    int center_x = game->screen_width / 2;
    int center_y =  game->screen_height / 2;

    if (x == center_x && y == center_y)
        return (0);

    int deltaX = x - center_x;
    int deltaY = y - center_y;

    double rotation = -deltaX * ROTATE_SPEED / 300.0;
    double oldDirX = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(rotation) - game->player.dir_y * sin(rotation);
    game->player.dir_y = oldDirX * sin(rotation) + game->player.dir_y * cos(rotation);
    double oldPlaneX = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(rotation) - game->player.plane_y * sin(rotation);
    game->player.plane_y = oldPlaneX * sin(rotation) + game->player.plane_y * cos(rotation);

    game->pitch -= deltaY * ROTATE_SPEED;
    if (game->pitch >  game->screen_height / 2)
        game->pitch =  game->screen_height / 2;
    if (game->pitch < - game->screen_height / 2)
        game->pitch = - game->screen_height / 2;

    mlx_mouse_move(game->mlx, game->win, center_x, center_y);

    return (0);
}

int main_loop(t_game *game)
{
    move_player(game);
    
    mlx_do_sync(game->mlx); // Synchronize events to allow both keyboard and mouse input
    draw_frame(game);
    return (0);
}

static void check_args(int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./cub3D <map_file>\n");
        exit(0);
    }
}

int main(int argc, char **argv)
{
    t_game  game;

    check_args(argc);
    check_map_file(&game, argv[1]);
    init_map_file(&game, argv[1]);
    check_map(&game);
    init_player(&game);
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game->screen_width,  game->screen_height, "cub3D");
    game.img = mlx_new_image(game.mlx, game->screen_width,  game->screen_height);
    game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &game.line_length, &game.endian);
    game.move_forward = 0;
    game.move_backward = 0;
    game.move_left = 0;
    game.move_right = 0;
    game.pitch = 0;
    mlx_mouse_hide(game.mlx, game.win);
    mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    mlx_loop_hook(game.mlx, main_loop, &game);
    mlx_loop(game.mlx);
    return (0);

}





*/

void load_textures(t_game *game)
{
    // Load North texture
    game->north_texture.img = mlx_xpm_file_to_image(
        game->mlx,
        "./img/n.xpm",
        &game->north_texture.width,
        &game->north_texture.height
    );
    if (!game->north_texture.img)
    {
        fprintf(stderr, "Error loading north texture\n");
        exit(EXIT_FAILURE);
    }
    game->north_texture.data = (int *)mlx_get_data_addr(
        game->north_texture.img,
        &game->north_texture.bits_per_pixel,
        &game->north_texture.line_length,
        &game->north_texture.endian
    );

    // Load South texture
    game->south_texture.img = mlx_xpm_file_to_image(
        game->mlx,
        "./img/s.xpm",
        &game->south_texture.width,
        &game->south_texture.height
    );
    if (!game->south_texture.img)
    {
        fprintf(stderr, "Error loading south texture\n");
        exit(EXIT_FAILURE);
    }
    game->south_texture.data = (int *)mlx_get_data_addr(
        game->south_texture.img,
        &game->south_texture.bits_per_pixel,
        &game->south_texture.line_length,
        &game->south_texture.endian
    );

    // Load West texture
    game->west_texture.img = mlx_xpm_file_to_image(
        game->mlx,
        "./img/w.xpm",
        &game->west_texture.width,
        &game->west_texture.height
    );
    if (!game->west_texture.img)
    {
        fprintf(stderr, "Error loading west texture\n");
        exit(EXIT_FAILURE);
    }
    game->west_texture.data = (int *)mlx_get_data_addr(
        game->west_texture.img,
        &game->west_texture.bits_per_pixel,
        &game->west_texture.line_length,
        &game->west_texture.endian
    );

    // Load East texture
    game->east_texture.img = mlx_xpm_file_to_image(
        game->mlx,
        "./img/e.xpm",
        &game->east_texture.width,
        &game->east_texture.height
    );
    if (!game->east_texture.img)
    {
        fprintf(stderr, "Error loading east texture\n");
        exit(EXIT_FAILURE);
    }
    game->east_texture.data = (int *)mlx_get_data_addr(
        game->east_texture.img,
        &game->east_texture.bits_per_pixel,
        &game->east_texture.line_length,
        &game->east_texture.endian
    );
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    if (y < 0 || y >=  game->screen_height || x < 0 || x >= game->screen_width)
        return;
    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_frame(t_game *game)
{
    for (int x = 0; x < game->screen_width; x++)
    {
        
        double cameraX = 2 * x / (double)game->screen_width - 1;
        double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
        double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
        int mapX = (int)game->player.player_x;
        int mapY = (int)game->player.player_y;
        double sideDistX;
        double sideDistY;
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;
        int stepX;
        int stepY;
        int hit = 0;
        int side;

        
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.player_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.player_x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.player_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.player_y) * deltaDistY;
        }
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->map.grid[mapX][mapY] == '1')
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - game->player.player_x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->player.player_y + (1 - stepY) / 2) / rayDirY;

        int lineheight = (int)( game->screen_height / perpWallDist);

        int drawStart = -lineheight / 2 +  game->screen_height / 2 + (int)game->pitch;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineheight / 2 +  game->screen_height / 2 + (int)game->pitch;
        if (drawEnd >=  game->screen_height)
            drawEnd =  game->screen_height - 1;

        // Select the correct texture
        t_texture *texture;
        if (side == 0)
        {
            if (rayDirX > 0)
                texture = &game->south_texture;  // West wall
            else
                texture = &game->north_texture;  // East wall
        }
        else
        {
            if (rayDirY > 0)
                texture = &game->east_texture; // North wall
            else
                texture = &game->west_texture; // South wall
        }

        // Calculate where exactly the wall was hit
        double wallX;
        if (side == 0)
            wallX = game->player.player_y + perpWallDist * rayDirY;
        else
            wallX = game->player.player_x + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        // x coordinate on the texture
        int texX = (int)(wallX * (double)(texture->width));
        if (side == 0 && rayDirX > 0)
            texX = texture->width - texX - 1;
        if (side == 1 && rayDirY < 0)
            texX = texture->width - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * texture->height / lineheight;
        // Starting texture coordinate
        double texPos = (drawStart -  game->screen_height / 2 + lineheight / 2 - game->pitch) * step;

        for (int y = 0; y <  game->screen_height; y++)
        {
            if (y < drawStart)
            {
                // Ceiling
                my_mlx_pixel_put(game, x, y, 0x87CEEB);
            }
            else if (y >= drawStart && y <= drawEnd)
            {
                int texY = (int)texPos & (texture->height - 1);
                texPos += step;

                int color = texture->data[texY * texture->width + texX];

                // Make color darker for Y-sides
                if (side == 1)
                    color = (color >> 1) & 8355711;

                my_mlx_pixel_put(game, x, y, color);
            }
            else
            {
                // Floor
                my_mlx_pixel_put(game, x, y, 0x228B22);
            }
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void move_player(t_game *game)
{
    if (game->move_forward)
    {
        if (game->map.grid[(int)(game->player.player_x + game->player.dir_x * MOVE_SPEED)][(int)(game->player.player_y)] != '1')
        {
            game->player.player_x += game->player.dir_x * MOVE_SPEED;
        }
        if (game->map.grid[(int)(game->player.player_x)][(int)(game->player.player_y + game->player.dir_y * MOVE_SPEED)] != '1')
        {
            game->player.player_y += game->player.dir_y * MOVE_SPEED;
        }
    }
    if (game->move_backward)
    {
        if (game->map.grid[(int)(game->player.player_x - game->player.dir_x * MOVE_SPEED)][(int)(game->player.player_y)] != '1')
        {
            game->player.player_x -= game->player.dir_x * MOVE_SPEED;
        }
        if (game->map.grid[(int)(game->player.player_x)][(int)(game->player.player_y - game->player.dir_y * MOVE_SPEED)] != '1')
        {
            game->player.player_y -= game->player.dir_y * MOVE_SPEED;
        }
    }
    if (game->move_right)
    {
        if (game->map.grid[(int)(game->player.player_x + game->player.plane_x * MOVE_SPEED)][(int)(game->player.player_y)] != '1')
        {
            game->player.player_x += game->player.plane_x * MOVE_SPEED;
        }
        if (game->map.grid[(int)(game->player.player_x)][(int)(game->player.player_y + game->player.plane_y * MOVE_SPEED)] != '1')
        {
            game->player.player_y += game->player.plane_y * MOVE_SPEED;
        }
    }
    if (game->move_left)
    {
        if (game->map.grid[(int)(game->player.player_x - game->player.plane_x * MOVE_SPEED)][(int)(game->player.player_y)] != '1')
        {
            game->player.player_x -= game->player.plane_x * MOVE_SPEED;
        }
        if (game->map.grid[(int)(game->player.player_x)][(int)(game->player.player_y - game->player.plane_y * MOVE_SPEED)] != '1')
        {
            game->player.player_y -= game->player.plane_y * MOVE_SPEED;
        }
    }
}


int key_press(int key, t_game *game)
{
    if (key == 65507) // ESC key
    {
        game->paused = 1;
        mlx_mouse_show(game->mlx, game->win);
    }
    if (key == 65307) // ESC key
    {
        exit(0);
    }
    if (key == 122) // W key
        game->move_forward = 1;
    if (key == 115) // S key
        game->move_backward = 1;
    if (key == 113) // A key
        game->move_left = 1;
    if (key == 100) // D key
        game->move_right = 1;
    return (0);
}

int key_release(int key, t_game *game)
{
    if (key == 65507) // ESC key
    {
        game->paused = 0;
        
        mlx_mouse_hide(game->mlx, game->win);
    }
    if (key == 122) // W key
        game->move_forward = 0;
    if (key == 115) // S key
        game->move_backward = 0;
    if (key == 113) // A key
        game->move_left = 0;
    if (key == 100) // D key
        game->move_right = 0;
    return (0);
}

int mouse_move(int x, int y, t_game *game)
{
    int center_x = game->screen_width / 2;
    int center_y =  game->screen_height / 2;
    static int f = 0;
    //mlx_mouse_hide(game->mlx, game->win);
    if (x != center_x && y != center_y && f == 0)
    {
        mlx_mouse_move(game->mlx, game->win, center_x, center_y);
        f = 1;
        return (0);
    }
        

    int deltaX = x - center_x;
    int deltaY = y - center_y;

    double rotation = -deltaX * ROTATE_SPEED / 300.0;
    double oldDirX = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(rotation) - game->player.dir_y * sin(rotation);
    game->player.dir_y = oldDirX * sin(rotation) + game->player.dir_y * cos(rotation);
    double oldPlaneX = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(rotation) - game->player.plane_y * sin(rotation);
    game->player.plane_y = oldPlaneX * sin(rotation) + game->player.plane_y * cos(rotation);

    game->pitch -= deltaY * ROTATE_SPEED;
    if (game->pitch >  game->screen_height / 2)
        game->pitch =  game->screen_height / 2;
    if (game->pitch < - game->screen_height / 2)
        game->pitch = - game->screen_height / 2;

    mlx_mouse_move(game->mlx, game->win, center_x, center_y);

    return (0);
}

int main_loop(t_game *game)
{
    if (game->paused)
        return (0);
    move_player(game);
    
    mlx_do_sync(game->mlx); // Synchronize events to allow both keyboard and mouse input
    draw_frame(game);
    return (0);
}

int main(int argc, char **argv)
{
	t_game	game;

    (void) game;
	if (argc != 2)
		(printf("Usage: ./cub3D maps/<map_file>\n"), exit(0));
	check_map_file(argv[1]);
    //init_map_file(&game, argv[1]);
   // check_map(&game);
    //init_player(&game);
    //init_game(&game, argv[1]);
    //printf("%f %f", game.player.player_x, game.player.player_y);
    //game.mlx = mlx_init();
   // check_game(&game);
    
    //mlx_get_screen_size(game.mlx, &game.screen_width, &game.screen_height);
    //load_textures(&game);
    //game.win = mlx_new_window(game.mlx, game.screen_width, game.screen_height, "cub3D");
    //game.img = mlx_new_image(game.mlx, game.screen_width, game.screen_height);
    //game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &game.line_length, &game.endian);
    //game.paused = 0;
    //game.move_forward = 0;
    //game.move_backward = 0;
    //game.move_left = 0;
    //game.move_right = 0;
    //game.pitch = 0;
    //game.player.player_dir = 'N';
    //game.player.player_x  = 5;
    //game.player.player_y = 5;
   // printf("%f %f", game.player.player_x, game.player.player_y);
    //mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
    //mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    //mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    //mlx_loop_hook(game.mlx, main_loop, &game);
    //mlx_mouse_hide(game.mlx, game.win);
    //int center_x = game.screen_width / 2;
    //int center_y = game.screen_height / 2;
    //mlx_mouse_move(game.mlx, game.win, center_x, center_y);
    //mlx_mouse_hide(game.mlx, game.win);
    //mlx_loop(game.mlx);
    return (0);
}














/*

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
		//if (ft_strlen(line) + 2 > game->map.width && i > 7)
		//	game->map.width = ft_strlen(line) + 2;
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
			if (!check_color(line))
				return (close(fd), free(line), 0);
		(free(line), i++);
	}
	return (close(fd), 1);
}
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>

#define WIN_game->screen_width 800
#define WIN_ game->screen_height 600
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05




void my_mlx_pixel_put(t_game *game, int x, int y, int color) {
    char *dst;

    dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void render_raycasting(t_game *game) {
    for (int x = 0; x < WIN_game->screen_width; x++) {
        double cameraX = 2 * x / (double)WIN_game->screen_width - 1;
        double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
        double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

        int mapX = (int)game->player.plane_x;
        int mapY = (int)game->player.plane_y;

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
            if (game->map.grid[mapX][mapY] > 0) hit = 1; // Hit a wall
        }

        // Calculate distance to the wall
        if (side == 0)
            perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / rayDirY;

        // Calculate the  game->screen_height of the line to draw
        int line game->screen_height = (int)(WIN_ game->screen_height / perpWallDist);
        int drawStart = -line game->screen_height / 2 + WIN_ game->screen_height / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = line game->screen_height / 2 + WIN_ game->screen_height / 2;
        if (drawEnd >= WIN_ game->screen_height) drawEnd = WIN_ game->screen_height - 1;

        // Set color based on side hit
        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

        // Draw the vertical line for the wall
        for (int y = drawStart; y < drawEnd; y++) {
            my_mlx_pixel_put(game, x, y, color);
        }

        // Draw the floor below the wall
        for (int y = drawEnd; y < WIN_ game->screen_height; y++) {
            my_mlx_pixel_put(game, x, y, game->image.floor_color);
        }

        // Draw the ceiling above the wall
        for (int y = 0; y < drawStart; y++) {
            my_mlx_pixel_put(game, x, y, game->image.ceiling_color);
        }
    }
}

void move_player(t_game *game) {
    double newX = game->player.player_x;
    double newY = game->player.player_y;

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
    render_raycasting(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
    return 0; // Return type should match the expected prototype
}




int	main(int argc, char **argv)
{
	t_game	game;

	
	
	game.mlx = mlx_init();
	check_game(&game);
	game.win = mlx_new_window(game.mlx, WIN_game->screen_width, WIN_ game->screen_height, "cub3D");
	mlx_hook(game.win, 17, 0, close_window, &game);
    game.image.img = mlx_new_image(game.mlx, WIN_game->screen_width, WIN_ game->screen_height);
    game.addr = mlx_get_data_addr(game.image.img, &game.bpp, &game.line_length, &game.endian);
    mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
    mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game);
    mlx_loop_hook(game.mlx, loop, &game);
    mlx_loop(game.mlx);
    clear_map(&game);
    clear_images(&game);
    mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
    return 0;
}
*/